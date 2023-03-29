/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:14:08 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/29 16:29:41 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	keep_print(t_cmd *data)
{
	if (data->input[0] == 34)
		trim_guil(data, 34);
	else if (data->input[0] == 39)
		trim_guil(data, 39);
	else
		trim_guil(data, 32);
}

/*
reste a mettre retour d'erreur de ce qui prend pas (/~), erreur ...*/
void	keep_option(t_cmd *data)
{
	if (strcmp(data->built, "echo") == 0 && strncmp(data->input, "-n ", 3) == 0)
		option(data, "-n", 1, 2);
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "../", 3) == 0)
	{
		option(data, "BACK", 1, 0);
		data->input[0] = '~';
		keep_option(data);
	}
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "..", 2) == 0)
	{
		option(data, "BACK", 1, 2);
		return ;
	}
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, ".", 1) == 0)
	{
		option(data, "STAY", 1, 1);
		return ;
	}
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "./", 2) == 0)
	{
		option(data, "STAY", 1, 2);
		keep_option(data);
	}
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "~/", 2) == 0)
		option(data, "FIND", 1, 0);
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "/", 1) == 0)
		option(data, "DIRECT", 1, 0);
	else if (strcmp(data->built, "cd") == 0)
		option(data, "HOME", 1, 0);//bug here
}

void	keep_builtin(int i, t_cmd *data)
{
	char	*str;

	data->input = ltrim(data->input);
	i = wordlen(data->input, i);
	str = ft_substr(data->input, 0, i);
	str = ulstr(str);//echo seulement
	str = trimchar(str, 32);
	data->built = str;
	data->input = wordtrim(data->input, i);
	data->input = ltrim(data->input); //echo hello < world -> must not work.
}

void	parse(t_cmd *data)
{
	int	i;

	i = 0;
	keep_builtin(i, data);
	keep_option(data);
	keep_print(data);
	keep_redir_input(data, i);
		/*input = keep_flag_delim(input, i);
		//input = keep_delimiter(input, i);
		printf("parse : %s\n", input);*/
}

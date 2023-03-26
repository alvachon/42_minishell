/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:14:08 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/26 19:20:02 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	keep_print(int i, t_cmd *data)
{
	if ((*data).input[0] != '<' || (*data).input[0] != '>'
		|| (*data).input[0] != '|')
	{
		if ((*data).input[0] == 34)
			trim_guil(&data, 34, 0);
		else if ((*data).input[0] == 39)
			trim_guil(&data, 39, 0);
		else
			trim_guil(&data, 0, 1);
	}
	i = ft_strlen((*data).print);
	while (i)
	{
		(*data).input++;
		i--;
	}
}

void	keep_option(t_cmd *data)
{
	if (strcmp(data->built, "echo") == 0 && strncmp(data->input, "-n ", 3) == 0)
		option(data, "-n", 1, 2);
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "..", 2) == 0)
		option(data, "BACK", 1, 2);
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, ".", 1) == 0)
		option(data, "STAY", 1, 1);
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "~/", 2) == 0)
		option(data, "FIND", 1, chartrim(data->input, ' '));
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "/", 1) == 0)
		option(data, "DIRECT", 0, 0);
	else if (strcmp(data->built, "cd") == 0)
		option(data, "HOME", 0, 0);
}

void	keep_builtin(int i, t_cmd *data)
{
	char	*str;

	data->input = ltrim(data->input);
	i = wordlen(data->input, i);
	str = ft_substr(data->input, 0, i);
	str = ulstr(str);
	str = trimchar(str, 32);
	data->built = str;
	data->input = wordtrim(data->input, i);
	data->input = ltrim(data->input);
}

t_cmd	parse(t_cmd data)
{
	int	i;

	i = 0;
	while (1)
	{
		keep_builtin(i, &data);
		keep_option(&data);
		keep_print(i, &data);
		/*input = keep_redir_input(input, i);
		input = keep_flag_delim(input, i);
		//input = keep_delimiter(input, i);
		printf("parse : %s\n", input);*/
		return (data);
	}
}

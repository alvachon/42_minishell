/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:14:08 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/05 20:07:26 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	keep_redir_input(t_cmd data, int i)
{
	(void)i;
	if (data.input[0] == '<' && data.input[1] <= 32)
	{
		data.redir_input = ft_substr(data.input, 0, 1);
		data.input++;
		data.input = ltrim(data.input);
	}
}

void	keep_flag_delim(t_cmd data, int i)
{
	if (data.input[0] == '<' && data.input[1] == '<')
	{
		data.flag_delim = ft_substr(data.input, 0, 2);
		i = 2;
		data.input = wordtrim(data.input, i);
		data.input = ltrim(data.input);
	}
}

void	keep_print(int i, t_cmd *data)
{
	if (data->input[0] == 34 || data->input[0] == 39)
		do_guil(data, i);
	else
		do_sp(data, i);
	while (scan(data->print, '$') == 0)
		do_ref(data, i);
}

void	keep_option(t_cmd *data)
{
	if (strcmp(data->built, "echo") == 0 && strncmp(data->input, "-n ", 3) == 0)
	{
		data->opt = "-n";
		data->input = wordtrim(data->input, 2);
		data->input = ltrim(data->input);
	}
	if (strcmp(data->built, "cd") == 0)
	{
		if (strncmp(data->input, "/", 1) != 0)
			do_relative_path(data);
		if (strncmp(data->input, ".", 1) == 0)
			data->input++;
		if (strncmp(data->input, "/", 1) == 0)
			do_direct_path(data);
	}
}

void	keep_builtin(int i, t_cmd *data)
{
	char	*str;

	data->input = ltrim(data->input);
	i = wordlen(data->input, i);
	str = ft_substr(data->input, 0, i);
	str = ulstr(str);//echo seulement
	str = trimchar(str, 32);
	data->built = ft_strdup(str);
	free (str);
	data->input = wordtrim(data->input, i);
	data->input = ltrim(data->input);
}

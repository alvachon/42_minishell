/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:14:08 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/12 14:16:52 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	keep_token(int i, t_cmd *data)
{
	if (ft_strncmp(data->input, "< ", 2) == 0)
		do_input(i, data);
	if (ft_strncmp(data->input, "<< ", 3) == 0)
		do_heredoc(i, data);
/*	if ((ft_strncmp(data->input, "> ", 2) == 0))
		do_output(i, data);*/
/*	else if (ft_strncmp(data->input, ">> ", 3) == 0)
		do_append();*/
/*	else if (ft_strncmp(data->input, "| ", 2) == 0)
		do_pipe();*/
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
	if (strcmp(data->built, "echo") == 0 && \
		strncmp(data->input, "-n ", 3) == 0)
	{
		data->opt = "-n";
		data->input = wordtrim(data->input, 2);
		data->input = ltrim(data->input);
	}
	if (strcmp(data->built, "cd") == 0)
	{
		if (strncmp(data->print, "/", 1) != 0)
			do_relative_path(data);
		if (strncmp(data->print, ".", 1) == 0)
			data->print++;
		if (strncmp(data->print, "/", 1) == 0)
			do_direct_path(data);
	}
}

void	keep_builtin(int i, t_cmd *data)
{
	char	*str;

	data->input = ltrim(data->input);
	/*if (ft_strncmp(data->input, "< ", 2) == 0)
		ft_swipe(data);*/
	/*if (is_fd() == 0)
		keep_fd();*/
	i = wordlen(data->input, i);
	str = ft_substr(data->input, 0, i);
	if (ft_strncmp(str, "ECHO", 5) == 0)
		str = ulstr(str);
	str = trimchar(str, 32);
	data->built = ft_strdup(str);
	free(str);
	data->input = wordtrim(data->input, i);
	data->input = ltrim(data->input);
}

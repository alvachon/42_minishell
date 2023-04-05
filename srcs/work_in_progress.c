/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_in_progress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:17:01 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/26 19:21:15 by alvachon         ###   ########.fr       */
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

/*
* End of the parsing for now  ( > | < )*/
char	*scan_end(char *file, int trig)
{
	char	**cmd;

	if (trig == 0)
	{
		printf("Watch out for < after guil \n");
		return (file);
	}
	if (scan(file, '<') == 0)
	{
		cmd = ft_split(file, '<');
		file = cmd[0];
		free(cmd);
	}
	if (scan(file, '>') == 0)
	{
		cmd = ft_split(file, '>');
		file = cmd[0];
		free(cmd);
	}
	if (scan(file, '|') == 0)
	{
		cmd = ft_split(file, '>');
		file = cmd[0];
		free(cmd);
	}
	return (file);
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

void	remove_section(t_cmd *data)
{
	int		index;
	char	*temp;

	index = 0;
	if (data->path[ft_strlen(data->path) - 1] == '/')
		index = 1;
	while (data->path[ft_strlen(data->path) - index - 1] != '/')
		index++;
	index = ft_strlen(data->path) - index;
	temp = ft_substr(data->path, 0, index);
	free(data->path);
	data->path = ft_strdup(temp);
	index = 2;
	while (index--)
		data->input++;
	free(temp);
}

/*int		index;
	char	*temp;

	index = 0;
	while (data->path[ft_strlen(data->path) - index] != '/')
		index++;
	index = ft_strlen(data->path) - index;
	if (index == 0)
		index = 1;
	temp = ft_substr(data->path, 0, index);
	free(data->path);
	data->path = ft_strdup(temp);
	index = 3;
	while (index--)
		data->input++;
	printf("%s/n", data->path);
	free (temp);*/
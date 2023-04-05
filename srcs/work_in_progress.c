/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_in_progress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:17:01 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/05 13:58:41 by alvachon         ###   ########.fr       */
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
char	*scan_end(t_cmd *data, int trig, char c)
{
	//char	**cmd;
	int		len;
	char	*file;

	file = NULL;
	if (trig == 1)
	{
		len = chartrim(data->input, c) - 1;
		file = ft_substr(data->input, 0, len);
		while (len--)
			data->input++;
		printf("se file : %s\n", file);
		printf("datas->input : %s\n", data->input);
		exit(1);
		return (file);
	}
	/*if (scan(file, '<') == 0)
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
	}*/
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

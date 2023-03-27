/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_in_progress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:17:01 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/27 09:58:08 by alvachon         ###   ########.fr       */
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
char	*scan_end(t_cmd *data, int trig)
{
	char	**cmd;
	int		i;

	i = 0;
	if (trig == 0)
	{
		printf("Watch out for < after guil \n");
		return (data->input);
	}
	if (scan(data->input, '<') == 0)
	{
		i = chartrim(data->input, '<');
		if (strcmp(data->built, "echo") == 0)
			data->print = trimchar(data->input, '<');
		while (i > 0)
		{
			data->input++;
			i--;
		}
		printf("%s\n", data->input);
	}
	if (scan(data->input, '>') == 0)
	{
		cmd = ft_split(data->input, '>');
		free(cmd);
	}
	if (scan(data->input, '|') == 0)
	{
		free(cmd);
	}
	return (data->input);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:14:08 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/11 14:53:35 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
cd < test.txt "/Users/alvachon" WORK
echo < test.txt BLANK // la il imprimme
a=5 export < test.txt "a" WORK
a=5 unset < test.txt "a" WORK
env < test.txt WORK (rien de special)//
pwd < test.txt WORK (rien de special)//
exit < test.txt WORK (rien de special)//
*/

void	keep_redir_input(int i, t_cmd *data)
{
	char	*read;
	char	*delim;
	int		fd;
	int		t;

	t = 0;
	delim = NULL;
	if (data->input[0] == '<' && data->input[1] <= 32)
	{
		data->input++;
		t = 1;
	}
	if (t > 0)
	{
		data->input = ltrim(data->input);
		fd = open(ft_substr(data->input, 0, wordlen(data->input, i)), O_RDONLY);
		if (fd == -1)
			return ; //
		while (data->input[0] > 32)
			data->input++;
		data->input = ltrim(data->input);
		if (data->input[0] == '<' && data->input[1] == '<')
		{
			data->input += 2;
			t = 2;
			data->input = ltrim(data->input);
			delim = ft_substr(data->input, 0, wordlen(data->input, i));
		}
		read = ft_readline(fd, t, delim);
		if (ft_strcmp(data->built, "cd") == 0)
			data->path = read;
		else
			data->print = read;
		close(fd);
		data->input = ltrim(data->input);
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
	/*if (strcmp(data->built, "echo") == 0 && strncmp(data->input, "-n ",
				3) == 0)
	{
		data->opt = "-n";
		data->input = wordtrim(data->input, 2);
		data->input = ltrim(data->input);
	}*/
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

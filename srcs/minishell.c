/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:55 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/24 15:30:42 by alvachon         ###   ########.fr       */
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

/*
! Define or enum the color system, too horrible this way [ ]
! Thinking about a function to return an anwser instead of  if if else if [ ]
* In the last else : Implementation of the pipe would be here I think ...
*/
int	main(int ac, char **av, char **env)
{
	t_terminal	minishell;
	char		*cmd;

	(void)av;
	if (ac != 2)
	{
		init_shell(&minishell, env);
		cmd = NULL;
		while (FOREGROUND_JOB)
		{
			if (isatty(STDIN_FILENO))
			{
				cmd = readline("\033[0m\033[34mminishell\033[0m\033[35m$ \033[0m");
				g_data.shell_state = SH_EXEC;
				if (!cmd)
					ctrl_c_eof();
				if (cmd[0] == '\0' || ft_strcmp(cmd, "\n") == 0)
				{
					if (cmd)
						free(cmd);
					continue ;
				}
				else if (lexer(cmd) == 1)
					error_msg(cmd);
				add_history(cmd);
				free(cmd);
				g_data.shell_state = SH_READ;
			}
			else
			{
				printf("\n(job process) Is redirected, not a terminal. \n");
			}
		}
	}
	sys_msg("Usage: Qt arg.\n", 2);
}

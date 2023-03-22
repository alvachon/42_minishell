/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:55 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/22 14:06:15 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* [0]BUILT [1]OPTION [2]REDIRECTION [3]APPEND [4]INFILE
* [5]PIPE [6]REDIRECTION [7]APPEND [8]OUTFILE */

#include "../includes/minishell.h"
#include <ctype.h> //

/*
! Move in a .c file for all trigger_utils checker[ ] */
int	envcheck(char **cmd)
{
	if (ft_strncmp(cmd[0], "$", 1) == 0)
		return (7);
	else
		return (8);
}

/*
! Change the function in a .c file with all to do with signal [ ]
! Verify that this write exit is legit or need implementation built in [ ]
SHELL -- Ctrl D that act like a ctrl C*/
void	ctrl_c_eof(void)
{
	rl_on_new_line();
	rl_redisplay();
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
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

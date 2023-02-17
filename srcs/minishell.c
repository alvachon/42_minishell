/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:55 by alvachon          #+#    #+#             */
/*   Updated: 2023/02/09 15:07:51 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* [0]BUILT [1]OPTION [2]REDIRECTION [3]APPEND [4]INFILE
* [5]PIPE [6]REDIRECTION [7]APPEND [8]OUTFILE */

#include "../includes/minishell.h"

int	envcheck(char **cmd)
{
	if (ft_strncmp(cmd[0], "$", 1) == 0)
		return (7);
	else
		return (8);
}

int	ft_getchar(void)
{
	char buf[BUFSIZ];
	char *bufptr;
	int i;

	bufptr = buf;
	i = 0;
	if (i == 0)
	{
		i = read(0, buf, 1);
		bufptr = buf;
	}
	if (--i >= 0)
		return (*bufptr++);
	return (0);
}

int main(int ac, char **av, char **env)
{
	t_terminal		minishell;
	char			*cmd;

	(void)av;
	if (ac != 2)
	{
		init_shell(&minishell);
  		while (FOREGROUND_JOB)
		{	
			if (isatty(STDIN_FILENO))
			{
    			cmd = readline("minishell$ ");
    			if (!cmd || cmd[0] == '\0' || ft_strcmp(cmd, "\n") == 0)
            	{
					if (cmd)
      		    		free(cmd);
      		    	continue;
    			}
    			else if (ft_strcmp(cmd, "exit") == 0)
					exit_msg(cmd, &minishell);
				else if (command_parse(cmd, env) == 1)
					error_msg(cmd);
				else
				{
					printf("Command done and freed, added to the history\n");
					add_history(cmd);
    				free(cmd);
				}
			}
			else //enter pipe process
			{
				printf("\n(job process) Is redirected, not a terminal. \n");
			}
  		}
	}
	sys_msg("Usage: Qt arg.\n", 2);
}

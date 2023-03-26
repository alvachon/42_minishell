/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:55 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/26 13:35:17 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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


int	shell_process(char **env)
{
	char		*cmd;

	cmd = NULL;
	while (isatty(STDIN_FILENO))
	{
		cmd = readline("\033[0m\033[34mminishell\033[0m\033[35m$ \033[0m");
		g_data.shell_state = SH_EXEC;
		if (!cmd)
			ctrl_c_eof();
		if (cmd[0] == '\0' || ft_strcmp(cmd, "\n") == 0)
			continue ;
		else if (lexer(cmd, env) == 1)
		{
			free (cmd);
			g_data.shell_state = SH_READ;
			return (1);
		}
		add_history(cmd);
		free(cmd);
		g_data.shell_state = SH_READ;
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_terminal	minishell;
	int			i;

	i = 0;
	if (ac != 2 && av)
	{
		init_shell(&minishell, env);
		while (FOREGROUND_JOB)
		{
			i = shell_process(env);
			if (i == 1)
				sys_msg("Usage: Lexer\n", 2);
			else if (i == 0)
				sys_msg("Usage: Pipe job\n", 2);
		}
	}
	sys_msg("Usage: Qt arg.\n", 2);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:43:24 by alvachon          #+#    #+#             */
/*   Updated: 2023/02/15 17:43:26 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void handle_sig(int sign)
{
	if (sign == SIGINT && g_data.shell_state == SH_READ)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "exit\n", 5);
		exit(EXIT_SUCCESS);
	}
	if (sign == SIGINT && g_data.shell_state == SH_EXEC)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

void	set_global(char **env)
{
	g_data.env = env;
	g_data.shell_state = SH_READ;
}

void	init_shell(t_terminal *minishell, char **env)
{
	set_global(env);
	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &(*minishell).mod_terminal);
		(*minishell).new_options = (*minishell).mod_terminal;
		(*minishell).new_options.c_cc[VEOF]     = 3;
		(*minishell).new_options.c_cc[VINTR]    = 4;
        (*minishell).new_options.c_cc[VQUIT]    = 0;
		tcsetattr(STDIN_FILENO,TCSANOW,&(*minishell).new_options);
		if (SIGINT)
		{
			(*minishell).new_options.c_lflag = ICANON | ECHO;
			tcsetattr(STDIN_FILENO,TCSANOW,&(*minishell).new_options);
			signal(SIGINT, handle_sig);
		}
	}
	else
	{
		if (!minishell)
			sys_msg("Not enough allocation for minishell\n", 2);
		sys_msg("init_shell : Not a terminal.\n", 2);
	}
}
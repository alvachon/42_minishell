/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_signal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:22:40 by alvachon          #+#    #+#             */
/*   Updated: 2023/05/17 08:53:29 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*

! Verify that this write exit is legit or need implementation built in [ ]
SHELL -- Ctrl D that act like a ctrl C*/
void	ctrl_c_eof(void)
{
	rl_on_new_line();
	rl_redisplay();
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
}

 SHELL - Signal Swipe Implementation */
void	handle_sig(int sign)
{
	if (sign == SIGINT && g_data.shell_state == SH_READ)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sign == SIGINT && g_data.shell_state == SH_EXEC)
		return ;
}

/*
SHELL -- Ctrl D that act like a ctrl C*/
void	ctrl_c_eof(void)
{
	rl_on_new_line();
	rl_redisplay();
	write(1, "exit\n", 5);
	exit(EXIT_SUCCESS);
}

/*

 SHELL - Grab terminal setting and adapt it for the sub (minishell) terminal */
void	init_shell(t_terminal *minishell, char **env)
{
	set_global(env);
	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &(*minishell).mod_terminal);
		(*minishell).new_options = (*minishell).mod_terminal;
		(*minishell).new_options.c_cc[VQUIT] = 0;
		tcsetattr(STDIN_FILENO, TCSANOW, &(*minishell).new_options);
		if (SIGINT)
		{
			(*minishell).new_options.c_lflag = ICANON | ECHO;
			tcsetattr(STDIN_FILENO, TCSANOW, &(*minishell).new_options);
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

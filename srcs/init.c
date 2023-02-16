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
	(void)sign;
	write(0, "minishell$ exit\n", 17);
	clear_history();
	exit(EXIT_SUCCESS);
}

void	init_shell(t_terminal *minishell)
{
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
		sys_msg("init_shell : Not a terminal.\n", 2);
}
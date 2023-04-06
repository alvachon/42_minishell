/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:55 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/05 20:21:53 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
			if (i > 0)
				sys_msg("Usage: Lexer\n", 2);
			else if (i == 0)
				sys_msg("Usage: Pipe job\n", 2);
		}
	}
	sys_msg("Usage: Qt arg.\n", 2);
}

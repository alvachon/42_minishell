/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:55 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/26 19:19:50 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	shell_process(char **env)
{
	char	*cmd;

	cmd = NULL;
	while (isatty(STDIN_FILENO))
	{
		cmd = readline("\033[0m\033[34mminishell\033[0m\033[35m$ \033[0m");
		g_data.shell_state = SH_EXEC;
		if (!cmd)
			ctrl_c_eof();
		if (cmd[0] == '\0' || ft_strcmp(cmd, "\n") == 0)
			continue ;
		else if (lexer(cmd, env) > 0)
		{
			free(cmd);
			g_data.shell_state = SH_READ;
			return (errno);
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
			if (i > 0)
				sys_msg("Usage: Lexer\n", 2);
			else if (i == 0)
				sys_msg("Usage: Pipe job\n", 2);
		}
	}
	sys_msg("Usage: Qt arg.\n", 2);
}

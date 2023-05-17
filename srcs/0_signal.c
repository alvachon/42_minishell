/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_signal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:22:40 by alvachon          #+#    #+#             */
/*   Updated: 2023/05/16 10:29:30 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*All signal reactions based on the terminal state (via enum)*/
void	handle_sig(int sign)
{
	if (sign == SIGINT && g_data.shell_state == SH_CHILD)
	{
		write(1, "\n", 1);
		return ;
	}
	else if (sign == SIGINT && g_data.shell_state == SH_EXEC)
		return ;
	else if (sign == SIGINT && g_data.shell_state == SH_READ)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

/*Reaction based on CTRL-D (EOF)*/
void	input_eof(void)
{
	write(0, "exit\n", 6);
	exit(EXIT_SUCCESS);
}

/*Function that control shell state with global enum*/
void	display_cmd(t_terminal *mini)
{
	g_data.shell_state = SH_READ;
	mini->cmd = readline(mini->prompt);
	g_data.shell_state = SH_EXEC;
}

/*Global data keeped in a single structure element*/
void	set_global(char **env)
{
	g_data.env = ft_setenv(env);
	g_data.shell_state = SH_READ;
	g_data.children = 0;
	g_data.pwd = ft_substr(set(1), 4, ft_strlen(set(1)));
	g_data.home = ft_substr(set(2), 5, ft_strlen(set(2)));
	g_data.retval = 0;
}

/*Initialisation of the terminal*/
void	init_shell(t_terminal *mini, char **env)
{
	set_global(env);
	mini->prompt = "minishell$ ";
	mini->cmd = NULL;
	mini->shell_terminal = STDIN_FILENO;
	mini->shell_is_interactive = isatty(mini->shell_terminal);
	if (mini->shell_is_interactive)
	{
		tcgetattr(mini->shell_terminal, &(*mini).mod_terminal);
		(*mini).new_options = (*mini).mod_terminal;
		(*mini).new_options.c_cc[VQUIT] = 0;
		tcsetattr(mini->shell_terminal, TCSANOW, &(*mini).new_options);
	}
	else
		perror("Not a terminal");
}

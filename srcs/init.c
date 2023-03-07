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
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sign == SIGINT && g_data.shell_state == SH_EXEC)
		return ;
}

char *set_pwd()
{
	int	i;
	char **cmd;
	char *file;

	i = 0;
	while (ft_strncmp("PWD=", g_data.env[i], 4) != 0)
		i++;
	cmd = ft_split(g_data.env[i], ':');
	file = cmd[0];
	file = ft_substr(file, 4, ft_strlen(file));
	return (file);
}

char *set_old_pwd()
{
	int	i;
	char **cmd;
	char *file;

	i = 0;
	while (ft_strncmp("OLDPWD=", g_data.env[i], 7) != 0)
		i++;
	cmd = ft_split(g_data.env[i], ':');
	file = cmd[0];
	file = ft_substr(file, 7, ft_strlen(file));
	return (file);
}

char *set_built_path()
{
	int	i;
	char **cmd;
	char *file;

	i = 0;
	while (ft_strncmp("PATH=", g_data.env[i], 5) != 0)
		i++;
	cmd = ft_split(g_data.env[i], ':');
	file = cmd[0];
	file = ft_substr(file, 5, ft_strlen(file));
	return (file);
}

void	set_global(char **env)
{
	g_data.env = env;
	g_data.shell_state = SH_READ;
	g_data.built_path = set_built_path();
	g_data.pwd = set_pwd();
	g_data.oldpwd = set_old_pwd();
	printf("\n MINISHELL INFO SETTING (g_var):\n");
	printf("- path : %s\n", g_data.built_path);
	printf("- pwd : %s\n", g_data.pwd);
	printf("- oldpwd : %s\n", g_data.oldpwd);
	printf("-----------\n");
}

void	init_shell(t_terminal *minishell, char **env)
{
	set_global(env);
	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &(*minishell).mod_terminal);
		(*minishell).new_options = (*minishell).mod_terminal;
		//(*minishell).new_options.c_cc[VEOF]     = 3;
		//(*minishell).new_options.c_cc[VINTR]    = 4;
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
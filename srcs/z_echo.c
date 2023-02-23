/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:22:05 by alvachon          #+#    #+#             */
/*   Updated: 2023/02/15 18:22:07 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_echo(char *exe_name, char *path, char **env, int code)
{
	int	i;

	i = 0;
	(void)env;
	if (code == 1)
		free(path);
	if (code == 2)
	{
		while (env[i])
		{
			free (env[i]);
			i++;
		}
		free (env);
		free (path);
		if (*exe_name)
			free (exe_name);
	}
	if (code == 3)
		free(exe_name);
}
void	execute_echo(char *path, char **cmd, char **env)
{
	pid_t	exe;
	int		i;
	int		j;

	i = -1;
	j = -1;
	exe = fork();
	if (exe == 0)
		execve(path, cmd, env);
	else
	{
		printf("execve(path, cmd, env); != 0\n");
		wait(0);
	}
	while (cmd[i++])
		free(cmd[i]);
	while (env[j++])
		free(env[j]);
	free (cmd);
	free (env);
	free (path);
	return ;
}

void	echo_parse(char **cmds, char **env)
{
	char	*exe_name;
	char	*path;
	int		i;

	i = 0;
	exe_name = ft_strjoin("/", g_data.input.built);
	while (env[i])
	{
		path = ft_strjoin(env[i], exe_name);
		if (access(path, F_OK) == 0)
		{
			execute_echo(path, cmds, env);
			free_echo(exe_name, path, env, 3);
			return ;
		}
		else
		{
			i++;
			free_echo(exe_name, path, env, 1);
		}
	}
	free_echo(exe_name, path, env, 2);
}
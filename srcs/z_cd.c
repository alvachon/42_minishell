/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:07:23 by alvachon          #+#    #+#             */
/*   Updated: 2023/02/21 13:07:24 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_cd(char *temp, char *path, char **env, int code)
{
	int	i;

	i = 0;
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
		if (*temp)
			free (temp);
	}
	if (code == 3)
		free(temp);
}

void    free_exect(char **cmd, char **env, char *path)
{
    int		i;
	int		j;

	i = -1;
	j = -1;
	while (cmd[i++])
		free(cmd[i]);
	while (env[j++])
		free(env[j]);
	free (cmd);
	free (env);
	free (path);
}

void	execute_cd(char *path, char **cmd, char **env)
{
	pid_t	exe;

	exe = fork();
	if (exe == 0)
		execve(path, cmd, env);
	else
		wait(0);
    free_exect(cmd, env, path);
	return ;
}

void	parse_cd(char **cmd, char **env)
{
	char	*file;
	char	*path;
	int		i;

	i = 0;
	file = ft_strjoin("/", cmd[0]);
	printf("%s\n", file);
	while (env[i])
	{
		path = ft_strjoin(env[i], file);
		printf("%s\n", path);
		if (access(path, F_OK) == 0)
		{
			execute_cd(path, cmd, env);
			free_cd(file, path, env, 3);
			return ;
		}
		else
		{
			i++;
			printf("... \n");
			//free_cd(file, path, env, 1);
		}
	}
	free_cd(file, path, env, 2);
}

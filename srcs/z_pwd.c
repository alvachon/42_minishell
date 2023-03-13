/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:23:42 by alvachon          #+#    #+#             */
/*   Updated: 2023/02/21 14:23:44 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

int	z_pwd(char **env);

/*void	free_pwd(char *temp, char *temp2, char **env, int code)
{
	int	i;

	i = 0;
	if (code == 1)
		free(temp2);
	if (code == 2)
	{
		while (env[i])
		{
			free (env[i]);
			i++;
		}
		free (env);
		free (temp2);
		if (*temp)
			free (temp);
	}
	if (code == 3)
		free(temp);
}

void	execute_pwd(char *path, char **cmd, char **env)
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
		wait(0);
	while (cmd[i++])
		free(cmd[i]);
	while (env[j++])
		free(env[j]);
	free (cmd);
	free (env);
	free (path);
	return ;
}

void	parse_pwd(char **cmd, char **env)
{
	char	*file;
	char	*path;
	int		i;

	i = 0;
	file = ft_strjoin("/", cmd[0]);
	while (env[i])
	{
		path = ft_strjoin(env[i], file);
		if (access(path, F_OK) == 0)
		{
			execute_pwd(path, cmd, env);
			free_pwd(file, path, env, 3);
			return ;
		}
		else
		{
			i++;
			free_pwd(file, path, env, 1);
		}
	}
	free_pwd(file, path, env, 2);
}
*/

int	z_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PWD=", 4) != 0)
		i++;
	printf("%s\n", ft_substr(env[i], 4, ft_strlen(env[i])));
	return (0);
}


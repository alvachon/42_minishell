/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:31:48 by fboulang          #+#    #+#             */
/*   Updated: 2023/04/11 13:54:08 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	z_unset(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g_data.env[i] && ft_strncmp(str, g_data.env[i], ft_strlen(str)) != 0)
		i++;
	if (g_data.env[i] == NULL)
		return (errno);
	else
	{
		g_data.env = env_unset(str);
	}
	return (errno);
}

char	**env_unset(char *str)
{
	char	**buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (g_data.env[i] != NULL)
		i++;
	buff = ft_calloc(i, sizeof(char *));
	i = 0;
	while (g_data.env[i] != NULL)
	{
		if (ft_unsetcomp(str, g_data.env[i]) == 0)
		{
			free(g_data.env[i]);
			i++;
		}
		if (g_data.env[i] != NULL)
			buff[j] = ft_strdup(g_data.env[i]);
		else
			return (buff);
		free(g_data.env[i]);
		i++;
		j++;
	}
	free(g_data.env);
	return (buff);
}

int	ft_unsetcomp(const char *str, char *var)
{
	int				i;
	int				j;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)str;
	b = (unsigned char *)var;
	j = ft_strlen(str);
	i = 0;
	while (i < j)
	{
		if (a[i] != b[i])
			return (1);
		i++;
	}
	if (var[i] == '=')
		return (0);
	return (1);
}

int	exec_bin(t_cmd *data)
{
	char	**temp;
	pid_t	child;

	if (access(data->built, F_OK) == 0)
	{
		child = fork();
		if (child == 0)
		{
			temp = paste_and_sep(data);
			execve(data->built, temp, g_data.env);
		}
		else
			wait(0);
	}
	return (errno);
}

int	ft_pathfinder(void)
{
	int	i;

	i = 0;
	while (g_data.env[i] != NULL && ft_strncmp(g_data.env[i], "PATH=", 5) != 0)
		i++;
	if (g_data.env[i] == NULL)
	{
		errno = 78;
		return (errno);
	}
	return (i);
}

/*char	*exec_rel(t_cmd *data)
{
	int		i;
	char	*temp;
	char	**buff;

	i = ft_pathfinder();
	if (i == errno)
		return (NULL);
	else
		temp = ft_substr(g_data.env[i], 5, ft_strlen(g_data.env[i]));
	i = 0;
	buff = ft_split(temp, ':');
	free (temp);
	temp = cmd_exists(buff, data);
}*/

/*char	*cmd_exists(char **paths, t_cmd *data)
{
	char	*temp;
	int		i;
	char	*cmd;

	cmd = ft_strdup(data->built);
	i = 0;
	while (paths[i] != NULL)
	{
		temp = ft_strjoin (paths[i], cmd);
		if (access (temp, F_OK) == 0)
		{
			free (cmd);
			return (temp);
		}
		i++;
		free (temp);
	}
	free (cmd);
	return (NULL);
}*/

char	**paste_and_sep(t_cmd *data)
{
	char	**buff;

	buff = NULL;
	if (data->print[0] != '\0')
	{
		printf("%s\n", data->print);
		buff = ft_calloc(3, sizeof(char *));
		buff[0] = ft_strdup(data->built);
		buff[1] = ft_strdup(data->print);
		buff[2] = NULL;
	}
	else if (data->print[0] == '\0')
	{
		buff = ft_calloc(2, sizeof(char *));
		buff[0] = ft_strdup(data->built);
		buff[1] = NULL;
	}
	return (buff);
}

/*bin = ft_strdup(data->built);
	args = ft_calloc(ft_strlen(bin) + ft_strlen(data->print) + 2, sizeof(char));
	i = 0;
	while (bin[i] != '\0')
	{
		args[i] = bin[i];
		i++;
	}
	args[i++] = ' ';
	while (data->print[0] != '\0')
	{
		args[i] = *data->print;
		data->print++;
		i++;
	}
	buff = ft_split(args, ' ');
	free (bin);
	free (args);
	char	**bin;
	char	**buff;
	int		i;
	int		j;

	i = 0;
	if (data->print == NULL)
		return (ft_split(data->built, ' '));
	bin = ft_split(data->print, ' ');
	while (bin[i] != NULL)
		i++;
	buff = ft_calloc(i + 2, sizeof(char *));
	j = i + 2;
	i = 1;
	buff[0] = ft_strdup(data->built);
	while (bin[i - 1] != NULL)
	{
		buff[i] = ft_strdup(bin[i - 1]);
		i++;
	}
	while (i++ < j)
		buff[i] = NULL;
	i = -1;
	while (bin[i++] != NULL)
		free(bin[i]);
	free(bin);*/

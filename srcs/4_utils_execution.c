/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_utils_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 08:49:47 by fboulang          #+#    #+#             */
/*   Updated: 2023/05/16 10:57:23 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Function to check if a system built in exist*/
char	*cmd_exists(char **paths, t_cmd *data)
{
	char	*temp;
	int		i;
	char	*cmd;

	cmd = ft_strjoin("/", data->built);
	i = 0;
	while (paths[i] != NULL)
	{
		temp = ft_strjoin(paths[i], cmd);
		if (access(temp, F_OK) == 0)
		{
			free(cmd);
			return (temp);
		}
		i++;
		free(temp);
	}
	free(cmd);
	return (NULL);
}

/*Function that take the retrived information and prepare it for execution*/
char	**paste_and_sep(t_cmd *data)
{
	char	**bin;
	char	**buff;
	t_in	ind;

	ind = init_ind();
	if (data->print == NULL)
		return (ft_split(data->built, ' '));
	bin = ft_split(data->print, ' ');
	while (bin[ind.i] != NULL)
		ind.i++;
	buff = ft_calloc(ind.i + 2, sizeof(char *));
	ind.j = ind.i + 2;
	ind.i = 1;
	buff[0] = ft_strdup(data->built);
	while (bin[ind.i - 1] != NULL)
	{
		buff[ind.i] = ft_strdup(bin[ind.i - 1]);
		ind.i++;
	}
	while (ind.i++ < ind.j)
		buff[ind.i] = NULL;
	free_the_vars(bin);
	return (buff);
}

/*Function that take information of the path*/
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

/*Control function before execution*/
int	get_rel(t_cmd *data, t_node *node)
{
	int		i;
	char	**buff;
	char	*temp;

	i = ft_pathfinder();
	if (i == errno)
		return (errno);
	temp = ft_substr(g_data.env[i], 5, ft_strlen(g_data.env[i]));
	buff = ft_split(temp, ':');
	free(temp);
	temp = cmd_exists(buff, data);
	if (temp == NULL)
		node->err = 5;
	free_buff(buff, i);
	if (temp == NULL)
		return (5);
	else
		return (exec_rel(node, temp));
}

/*Verify if the command is built in*/
int	builtin_check(t_node *node)
{
	if (ft_strncmp(node->job.built, "echo", 5) == 0)
		return (0);
	if (ft_strncmp(node->job.built, "cd", 3) == 0)
		return (0);
	if (ft_strncmp(node->job.built, "pwd", 4) == 0)
		return (0);
	if (ft_strncmp(node->job.built, "export", 7) == 0)
		return (0);
	if (ft_strncmp(node->job.built, "unset", 6) == 0)
		return (0);
	if (ft_strncmp(node->job.built, "env", 4) == 0)
		return (0);
	if (ft_strncmp(node->job.built, "exit", 5) == 0)
		return (0);
	else
		return (1);
	return (1);
}

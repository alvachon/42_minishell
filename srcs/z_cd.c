/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:39:03 by fboulang          #+#    #+#             */
/*   Updated: 2023/05/16 10:48:37 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	trim_spec(int code, t_node *node)
{
	if (code == 0)
		node->input += 1;
	if (code == 1)
		node->input += 2;
	node->input = ltrim(node->input);
}

char	*subtrim(int i, t_node *node)
{
	char	*temp;
	int		j;

	j = wordlen(node->input, i);
	temp = ft_substr(node->input, 0, j);
	if (j > token_reach(i, temp))
	{
		j = token_reach(i, temp);
		free (temp);
		temp = ft_substr(node->input, 0, j);
	}
	temp = trimchar(temp, 34);
	temp = trimchar(temp, 39);
	return (temp);
}

void	remove_section(t_node *node)
{
	int		index;
	char	*temp;

	index = 0;
	if (node->job.path[ft_strlen(node->job.path) - 1] == '/')
		index = 1;
	while (node->job.path[ft_strlen(node->job.path) - index - 1] != '/')
		index++;
	index = ft_strlen(node->job.path) - index;
	temp = ft_substr(node->job.path, 0, index);
	free(node->job.path);
	node->job.path = ft_strdup(temp);
	index = 2;
	while (index--)
		node->job.temp++;
	free(temp);
}

void	add_section(t_node *node)
{
	int		i;
	char	*buff;

	i = 0;
	i = chartrim(node->job.temp, '/');
	if (i == 0)
		i = 1;
	buff = ft_substr(node->job.temp, 0, i);
	if (buff[0] == '/' && node->job.path[ft_strlen(node->job.path) - 1] == '/')
	{
		free(buff);
		node->job.temp++;
		return ;
	}
	node->job.path = ft_strpaste(node->job.path, buff);
	while (i--)
		node->job.temp++;
	if (buff != NULL)
		free(buff);
}

int	z_cd(t_cmd data)
{
	char	*temp;
	char	*temp2;
	int		i;

	i = chdir(data.path);
	if (i == -1)
		write(2, "minishell : No such file or directory\n", 39);
	if (i == -1)
		return (2);
	temp = ft_strjoin("OLDPWD=", g_data.pwd);
	z_export(temp);
	free(g_data.pwd);
	if (data.path[ft_strlen(data.path) - 1] == '/')
	{
		temp2 = ft_substr(data.path, 0, ft_strlen(data.path) - 1);
		g_data.pwd = ft_strdup(temp2);
		free(temp2);
	}
	else
		g_data.pwd = ft_strdup(data.path);
	free(temp);
	temp = ft_strjoin("PWD=", g_data.pwd);
	z_export(temp);
	free(temp);
	return (errno);
}

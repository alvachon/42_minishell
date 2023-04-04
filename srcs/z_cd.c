/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/04 12:31:44 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	delete_last(t_cmd data)
{
	char	*str;
	int		i;
	int		c;

	i = 0;
	str = data.path;
	while (str[i])
		i++;
	c = i;
	while (str[i] != '/')
		i--;
	return (c - i);
}

char	*rewrite(t_cmd *data, int i)
{
	int	j;

	j = 0;
	while (data->path[j])
		j++;
	j -= i;
	i = 0;
	while (i < j)
		i++;
	data->path[i] = '\0';
	return (data->path);
}

void	keep_user(t_cmd *data)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (c != 3)
	{
		if (data->path[i] == '/')
			c++;
		i++;
	}
	data->path[i - 1] = '\0';
}
int	z_cd(t_cmd data, char **env)
{
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	(void)env;
	if (strcmp(data.opt, "BACK") == 0)
		data.path = rewrite(&data, delete_last(data));
	if (strcmp(data.opt, "STAY") == 0 || strcmp(data.opt, "FIND") == 0 || strcmp(data.opt, "DIRECT") == 0)
		data.path = data.path;
	if (strcmp(data.opt, "HOME") == 0)
		keep_user(&data);
	chdir(data.path);
	if (data.path[0] == '\0')
		data.path[0] = '/';
	while (g_data.env[i] && ft_strncmp(g_data.env[i], "PWD=", 4) != 0)
		i++;
	temp2 = ft_substr(g_data.env[i], 4, ft_strlen(g_data.env[i]));
	temp = ft_strjoin ("OLDPWD=", temp2);
	z_export(temp);
	free (temp);
	temp = ft_strjoin("PWD=", data.path);
	z_export(temp);
	free(temp2);
	free(temp);
	return (errno);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/05 14:01:04 by alvachon         ###   ########.fr       */
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

int	z_cd(t_cmd data)
{
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	i = chdir(data.path);
	if (i == -1)
		return (errno);
	temp = ft_strjoin("OLDPWD=", g_data.pwd);
	z_export(temp);
	free (g_data.pwd);
	if (data.path[ft_strlen(data.path) -1] == '/')
	{
		temp2 = ft_substr(data.path, 0, ft_strlen(data.path) - 1);
		g_data.pwd = ft_strdup (temp2);
		free (temp2);
	}
	else
		g_data.pwd = ft_strdup(data.path);
	free (temp);
	temp = ft_strjoin("PWD=", g_data.pwd);
	z_export(temp);
	free(temp);
	return (errno);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/26 15:43:29 by alvachon         ###   ########.fr       */
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

void	rewrite(t_cmd data, int i)
{
	int	 j;

	j = 0;
	while (data.path[j])
		j++;
	j -= i;
	i = 0;
	while (i < j)
		i++;
	data.path[i] = '\0';
}

int	z_cd(t_cmd data, char **env)
{
	char	*temp;
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	if (strcmp(data.opt, "..") == 0)
		rewrite(data, delete_last(data));
	chdir(data.path);
	while (env[i] && ft_strncmp(env[i], "PWD=", 4) != 0)
		i++;
	temp = ft_substr(env[i], 4, ft_strlen(env[i]));
	//free (env[i]);
	env[i] = ft_strjoin("PWD=", data.path);
	while (env[i] && ft_strncmp(env[i], "OLDPWD=", 7) != 0)
		i++;
	//free (env[i]);
	env[i] = ft_strjoin("OLDPWD=", temp);
	free (temp);
	return (0);
}

/* faut parser les ../ pour que ça donne un path complet pour pwd*/


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:43:24 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/24 15:35:55 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*path(char *home)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (home[i])
	{
		if (home[i] == '/')
			c++;
		if (c == 3)
			break ;
		i++;
	}
	i++;
	home[i] = '\0';
	return (home);
}

/*
 UTILS - Isolate a chosen data array from our collected env path */
char	*set(char *var, int siz_var)
{
	int		i;
	char	**cmd;
	char	*file;

	i = 0;
	while (ft_strncmp(var, g_data.env[i], siz_var) != 0)
		i++;
	cmd = ft_split(g_data.env[i], ':');
	file = cmd[0];
	file = ft_substr(file, siz_var, ft_strlen(file));
	free(cmd);
	return (file);
}

/*
 UTILS -  Get Path env system */
char	**paths_search(void)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH=", g_data.env[i], 5) != 0)
		i++;
	return (ft_split(g_data.env[i], ':'));
}


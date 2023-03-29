/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:31:48 by fboulang          #+#    #+#             */
/*   Updated: 2023/03/26 19:21:06 by alvachon         ###   ########.fr       */
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
	return (buff);
}

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

int	z_unset(char *str, char **env)
{
	int		i;
	int		j;
	char	**temp;

	i = 0;
	j = 0;
	temp = ft_split(str, ' ');
	while (env[i] && ft_strncmp(temp[1], env[i], ft_strlen(temp[1])) != 0)
		i++;
	if (env[i] == NULL)
		return (0);
	else
	{
		g_data.env = env_unset(temp[1], g_data.env);
	}
	return (errno);
}

char	**env_unset(char *str, char **env)
{
	char	**buff;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (env[i] != NULL)
		i++;
	buff = ft_calloc(i - 1, sizeof(char *));
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_unsetcomp(str, env[i]) == 0)
		{
			//free(env[i]);
			i++;
		}
		if (env[i] != NULL)
			buff[j] = ft_strdup(env[i]);
		else
			return (buff);
		//free(env[i]);
		i++;
		j++;
	}
	return (buff);
}

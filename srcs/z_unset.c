/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <fboulang@42student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:31:48 by fboulang          #+#    #+#             */
/*   Updated: 2023/03/08 12:31:50 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	z_unset(char *str, char **env)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i] && ft_strncmp(str, env[i], ft_strlen(str)) != 0)
		i++;
	if (env[i] == NULL)
		return (0);
	else
		env = env_unset(str, env);
	return (0);
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
	buff = ft_calloc (i - 1, sizeof(char *));
	i = 0;
	while (env[i] != NULL)
	{
		if (ft_strncmp(str, env[i], ft_strlen(str)) == 0)
		{
			free(env[i]);
			i++;
		}
		ft_memmove(buff[j], env[i], ft_strlen(env[i]));
		free (env[i]);
		i++;
		j++;
	}
	free (env);
	return (buff);
}
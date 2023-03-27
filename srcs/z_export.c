/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:56:34 by fboulang          #+#    #+#             */
/*   Updated: 2023/03/26 17:39:58 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	z_export(char *str, char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], str, ft_strlen(str)) != 0)
		i++;
	if (env[i] == NULL)
		env = export_env(str, env);
	else
		env[i] = new_env_var(str, env[i]);
	return (errno);
}

char	**export_env(char *str, char **env)
{
	char	**buff;
	int		i;

	i = 0;
	while (env[i])
		i++;
	buff = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (env[i])
	{
		ft_memmove(buff[i], env[i], ft_strlen(env[i]));
		free(env[i]);
		i++;
	}
	buff[i] = str;
	//free(env);
	return (buff);
}

char	*new_env_var(char *str, char *var)
{
	free(var);
	var = ft_strdup(str);
	return (var);
}

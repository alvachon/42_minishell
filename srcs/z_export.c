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
	char	**temp;

	i = 0;
	temp = ft_split(str, ' ');
	while (env[i] && ft_strncmp(env[i], temp[1], ft_strlen(str)) != 0)
		i++;
	if (env[i] == NULL)
		g_data.env = export_env(temp[1], env);
	else
		env[i] = new_env_var(temp[1], env[i]);
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
		buff[i] = ft_strdup(env[i]);
		printf("%s\n", buff[i]);
		//free(env[i]);
		i++;
	}
	buff[i] = ft_strdup(str);
	printf("%s\n", buff[i]);
	//free(env);
	return (buff);
}

char	*new_env_var(char *str, char *var)
{
	//free(var);
	var = ft_strdup(str);
	return (var);
}

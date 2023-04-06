/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:56:22 by fboulang          #+#    #+#             */
/*   Updated: 2023/04/05 20:17:54 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	z_env(char **env)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	(void)env;
	while (g_data.env[i] != NULL)
		i++;
	while (++j < i)
		printf("%s\n", env[j]);
	return (errno);
}

int	z_pwd(char **env)
{
	int		i;
	char	*temp;

	i = 0;
	temp = NULL;
	while (g_data.env[i] && ft_strncmp(g_data.env[i], "PWD=", 4) != 0)
		i++;
	if (g_data.env[i] != NULL)
		temp = ft_substr(g_data.env[i], 4, ft_strlen(g_data.env[i]));
	else if (g_data.env[i] == NULL)
	{
		i = 0;
		while (env[i] && ft_strncmp(env[i], "PWD=", 4) != 0)
			i++;
		temp = ft_substr(env[i], 4, ft_strlen(env[i]));
	}
	printf("%s\n", g_data.pwd);
	free (temp);
	return (errno);
}

int	z_exit(t_cmd data, int status)
{
	int	i;

	i = 0;
	if (!status)
		status = 0;
	while (g_data.env[i] != NULL)
	{
		free(g_data.env[i]);
		i++;
	}
	data_free(&data);
	free(g_data.env);
	free (g_data.pwd);
	exit (status);
}

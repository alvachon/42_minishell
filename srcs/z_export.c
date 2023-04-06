/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:56:34 by fboulang          #+#    #+#             */
/*   Updated: 2023/04/05 20:20:57 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	z_export(char *str)
{
	int	i;

	i = 0;
	while (g_data.env[i] && ft_exportcomp(str, g_data.env[i]) != 0)
		i++;
	if (g_data.env[i] == NULL)
		g_data.env = export_env(str);
	else
		g_data.env[i] = new_env_var(str, i);
	return (errno);
}

char	**export_env(char *str)
{
	char	**buff;
	int		i;

	i = 0;
	while (g_data.env[i])
		i++;
	buff = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (g_data.env[i])
	{
		buff[i] = ft_strdup(g_data.env[i]);
		free(g_data.env[i]);
		i++;
	}
	buff[i] = ft_strdup(str);
	free(g_data.env);
	return (buff);
}

char	*new_env_var(char *str, int pos)
{
	char	*temp;

	if (g_data.env[pos])
		free(g_data.env[pos]);
	temp = ft_strdup(str);
	return (temp);
}

int	ft_exportcomp(const char *str, char *var)
{
	int				i;
	int				j;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)str;
	b = (unsigned char *)var;
	j = ft_strlen(str);
	i = 0;
	while (i < j && a[i] != '=')
	{
		if (a[i] != b[i])
			return (1);
		i++;
	}
	if (var[i] == '=')
		return (0);
	return (1);
}

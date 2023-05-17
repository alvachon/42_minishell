/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_export.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:56:34 by fboulang          #+#    #+#             */
/*   Updated: 2023/05/17 08:54:30 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	z_export(char *str)
{
	char	**vars;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (identchecker(str) == 4)
	{
		return (4);
	}
	vars = ft_split(str, ' ');
	while (vars[j] != NULL)
	{
		while (g_data.env[i] && ft_exportcomp(vars[j], g_data.env[i]) != 0)
			i++;
		if (g_data.env[i] == NULL)
			g_data.env = export_env(vars[j]);
		else
			g_data.env[i] = new_env_var(vars[j], i);
		j++;
	}
	free_the_vars(vars);
	return (errno);
}

char	**export_env(char *str)
{
	char	**buff;
	int		i;
	int		j;

	i = 0;
	while (g_data.env[i] != NULL)
		i++;
	j = i;
	buff = ft_calloc(i + 2, sizeof(char *));
	i = 0;
	while (g_data.env[i] != NULL && i < j)
	{
		buff[i] = ft_strdup(g_data.env[i]);
		free(g_data.env[i]);
		i++;
	}
	buff[i] = ft_strdup(str);
	buff[i + 1] = NULL;
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

int	identchecker(char *str)
{
	int	i;

	i = 0;
	if (ft_strncmp(str, "=", 1) == 0)
	{
		return (4);
	}
	while (str[i] != '\0' && str[i] != '=')
	{
		if (str[i] == '+')
			return (4);
		if (str[i] == '-')
			return (4);
		i++;
	}
	return (0);
}

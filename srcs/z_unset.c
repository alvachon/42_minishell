/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 12:31:48 by fboulang          #+#    #+#             */
/*   Updated: 2023/05/08 15:49:14 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	z_unset(char *str)
{
	char	**vars;
	t_in	ind;

	ind = init_ind();
	vars = ft_split(str, ' ');
	while (vars[ind.j] != NULL)
	{
		while (g_data.env[ind.i] && ft_strncmp(vars[ind.j], g_data.env[ind.i],
				ft_strlen(vars[ind.j])) != 0)
			ind.i++;
		if (g_data.env[ind.i] == NULL)
		{
			ind.j++;
			ind.i = 0;
		}
		else
		{
			g_data.env = env_unset(vars[ind.j]);
			ind.j++;
			ind.i = 0;
		}	
	}
	free_the_vars(vars);
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
	buff = ft_calloc(i + 1, sizeof(char *));
	i = 0;
	while (g_data.env[i] != NULL)
	{
		if (ft_unsetcomp(str, g_data.env[i]) == 0)
			i++;
		if (g_data.env[i] == NULL)
			break ;
		buff[j] = ft_strdup(g_data.env[i]);
		i++;
		j++;
	}
	free_the_env();
	buff[j] = NULL;
	return (buff);
}

int	ft_unsetcomp(const char *str, char *var)
{
	int				i;
	int				j;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)str;
	b = (unsigned char *)var;
	j = ft_strlen(str);
	i = 0;
	while (i < j)
	{
		if (a[i] != b[i])
			return (1);
		i++;
	}
	if (var[i] == '=')
		return (0);
	return (1);
}

void	free_the_vars(char **vars)
{
	int	j;

	j = 0;
	while (vars[j] != NULL)
	{
		free(vars[j]);
		j++;
	}
	free(vars);
}

void	free_the_env(void)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (g_data.env[i] != NULL)
		i++;
	while (j < i)
	{
		free(g_data.env[j]);
		j++;
	}
	free(g_data.env);
}

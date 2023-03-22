/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 12:00:29 by fboulang          #+#    #+#             */
/*   Updated: 2023/03/22 15:23:36 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
! Faut parser les ../ pour que ça donne un path complet pour pwd [ ]*/

int	z_cd(char *str, char **env)
{
	char	*temp;
	int		i;

	i = 0;
	chdir(str);
	while (env[i] && ft_strncmp(env[i], "PWD=", 4) != 0)
		i++;
	temp = ft_substr(env[i], 4, ft_strlen(env[i]));
	free (env[i]);
	env[i] = ft_strjoin("PWD=", str);
	while (env[i] && ft_strncmp(env[i], "OLDPWD=", 7) != 0)
		i++;
	free (env[i]);
	env[i] = ft_strjoin("OLDPWD=", temp);
	free (temp);
	return (0);
}

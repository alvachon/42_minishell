/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 09:07:14 by fboulang          #+#    #+#             */
/*   Updated: 2023/03/15 09:07:15 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	z_exit(int status)
{
	free(g_data.built_path);
	while (*g_data.env)
	{
		free(*g_data.env);
		*g_data.env++;
	}
	free(g_data.pwd);
	free(g_data.oldpwd);
	return (status);
}

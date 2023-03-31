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

int	z_exit(t_cmd data, int status)
{
	int	i;

	i = 0;
	if (!status)
		status = 0;
	free(g_data.built_path);
	while (g_data.env[i] != NULL)
	{
		free(g_data.env[i]);
		i++;
	}
	free (data.print);
	free (data.input);
	free (data.built);
	free (g_data.pwd);
	free (g_data.env);
	free (data.path);
	exit (status);
}

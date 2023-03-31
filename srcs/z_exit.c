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

void	data_free(t_cmd *data)
{
	if (data->built)
		free (data->built);
	if (data->path)
		free (data->path);
	return ;
}

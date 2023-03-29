/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:56:22 by fboulang          #+#    #+#             */
/*   Updated: 2023/03/22 15:21:54 by alvachon         ###   ########.fr       */
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

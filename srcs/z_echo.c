/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:22:05 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/29 11:08:43 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	z_echo(t_cmd data, char **env)
{
	(void)env;
	printf("at echo\n");
	if (strcmp(data.opt, "-n") == 0)
		printf("%s", data.print);
	else
		printf("%s\n", data.print);
}

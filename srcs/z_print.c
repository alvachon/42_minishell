/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_print.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 10:56:22 by fboulang          #+#    #+#             */
/*   Updated: 2023/05/17 08:54:40 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	z_env(void)
{
	int	i;
	int	j;

	i = 0;
	j = -1;
	while (g_data.env[i] != NULL)
		i++;
	while (++j < i)
		printf("%s\n", g_data.env[j]);
	return (errno);
}

int	z_pwd(t_node *node)
{
	int		i;

	i = 0;
	while (g_data.pwd[i] != '\0')
	{
		write(node->job.out, &g_data.pwd[i], 1);
		i++;
	}
	write(node->job.out, "\n", 1);
	return (errno);
}

int	z_exit(t_node *node, char *status)
{
	int	code;

	write(2, "exit\n", 6);
	if (isallnum(status) == 2)
		code = 0;
	else if (isallnum(status) == 1)
	{
		ft_errormsg(3);
		code = 255;
	}
	else
		code = ft_atoi(status);
	close(node->fds[1]);
	close(node->fds[0]);
	data_free(node);
	free_the_env();
	free (g_data.pwd);
	exit (code);
}

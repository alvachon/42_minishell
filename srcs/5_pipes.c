/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_pipes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 11:47:07 by fboulang          #+#    #+#             */
/*   Updated: 2023/05/08 15:38:33 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	child_pipe_in(t_node *node, int code)
{
	if (node->index == 0)
	{
		close(node->fds[0]);
		dup2(node->fds[1], STDOUT_FILENO);
		close(node->fds[1]);
		close(node->next->fds[1]);
		close(node->next->fds[0]);
	}
	else
	{
		close(node->fds[0]);
		dup2(node->prev->fds[0], STDIN_FILENO);
		close(node->prev->fds[0]);
		dup2(node->fds[1], STDOUT_FILENO);
		close(node->fds[1]);
		close(node->prev->fds[1]);
	}
	if (code == 1)
		return (0);
	else if (code == 0)
		return (exect_cmd(node));
	else
		return (errno);
}

int	pipe_out(t_node *node, int code)
{
	close(node->prev->fds[1]);
	dup2(node->prev->fds[0], STDIN_FILENO);
	close(node->prev->fds[0]);
	close(node->fds[0]);
	close(node->fds[1]);
	if (code == 1)
		return (0);
	else if (code == 0)
		return (exect_cmd(node));
	else
		return (errno);
}

int	pipers(t_node *process)
{
	pid_t	parent;
	int		r;
	int		status;

	r = 0;
	status = 0;
	parent = fork();
	if (parent == 0)
	{
		if (process->next)
			r = child_pipe_in(process, 0);
		else if (!process->next)
			r = pipe_out(process, 0);
		exit(r);
	}
	else if (parent < 0)
	{
		perror("fork");
		exit(1);
	}
	else
		wait(0);
	return (g_data.retval = r);
}

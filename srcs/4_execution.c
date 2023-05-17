/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_execution.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 08:48:17 by fboulang          #+#    #+#             */
/*   Updated: 2023/05/16 10:52:50 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Execute the command based on node information (error, homemade, system)*/
int	exect_cmd(t_node *node)
{
	int	r;

	r = node->err;
	if (node->err > 0)
		return (ft_errormsg(r));
	else if (ft_strncmp(node->job.built, "echo", 5) == 0)
		r = z_echo(node->job, g_data.env);
	else if (ft_strncmp(node->job.built, "cd", 3) == 0)
		r = z_cd(node->job);
	else if (ft_strncmp(node->job.built, "pwd", 4) == 0)
		r = z_pwd(node);
	else if (ft_strncmp(node->job.built, "export", 7) == 0)
		r = z_export(node->job.print);
	else if (ft_strncmp(node->job.built, "unset", 6) == 0)
		r = z_unset(node->job.print);
	else if (ft_strncmp(node->job.built, "env", 4) == 0)
		r = z_env();
	else if (ft_strncmp(node->job.built, "exit", 5) == 0)
		return (z_exit(node, node->job.print));
	else
		r = ft_dispatch_exec(node);
	if (node->err == 0)
		data_free(node);
	return (g_data.retval = ft_errormsg(r));
}

/*Dispatch execution for system bin or relative path with error handling*/
int	ft_dispatch_exec(t_node *node)
{
	if (node->job.in == -1 || node->job.out == -1)
		return (2);
	if (node->job.built[0] == '\0')
		return (0);
	if (ft_strncmp(node->job.built, "/", 1) == 0)
	{
		if (access(node->job.built, F_OK) != 0)
			return (5);
		return (exec_bin(node));
	}
	else
		return (get_rel(&node->job, node));
}

/*children process for the execution*/
void	exec_child(t_node *node, char *path)
{
	char	**temp;

	if (!path)
		path = node->job.built;
	temp = paste_and_sep(&node->job);
	if (node->index >= 0 && node->index != g_data.pipenum
		&& g_data.pipenum != 0)
		child_pipe_in(node, 1);
	else if (node->index == g_data.pipenum && g_data.pipenum > 0)
		pipe_out(node, 1);
	if (node->job.out != STDOUT_FILENO)
	{
		dup2(node->job.out, STDOUT_FILENO);
		close(node->job.out);
	}
	if (node->job.in != 0)
	{
		dup2(node->job.in, STDIN_FILENO);
		close(node->job.in);
	}	
	execve(path, temp, g_data.env);
	perror("execve:");
	exit(errno);
	if (access(node->job.built, F_OK) != 0)
		exit(errno);
}

/*parent process for*/
int	exec_rel(t_node *node, char *path)
{
	pid_t		child;
	int			status;

	status = 0;
	child = fork();
	if (child == 0)
		exec_child(node, path);
	else if (child != 0 && node->index > 0)
	{
		close(node->prev->fds[1]);
		close(node->prev->fds[0]);
	}
	else if (child != 0 && node->index == g_data.pipenum && g_data.pipenum != 0)
		close(node->prev->fds[1]);
	if (child != 0)
	{
		g_data.shell_state = SH_CHILD;
		waitpid(0, &status, 0);
	}
	if (node->job.in != STDIN_FILENO)
		close(node->job.in);
	if (node->job.out != STDOUT_FILENO)
		close(node->job.out);
	free(path);
	return (errno);
}

/*parent process for*/
int	exec_bin(t_node *node)
{
	pid_t	child;
	int		status;

	status = 0;
	child = fork();
	if (child == 0)
		exec_child(node, NULL);
	else if (child < 0)
	{
		perror("fork");
		exit(1);
	}
	else if (child != 0 && node->index > 0)
	{
		close(node->prev->fds[0]);
		close(node->fds[1]);
	}
	if (child != 0)
		waitpid(0, &status, 0);
	if (node->job.in != STDIN_FILENO)
		close(node->job.in);
	if (node->job.out != STDOUT_FILENO)
		close(node->job.out);
	return (errno);
}

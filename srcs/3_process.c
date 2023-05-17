/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_process.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:25 by alvachon          #+#    #+#             */
/*   Updated: 2023/05/16 10:48:34 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Function to free data and close pipes of the node*/
void	data_free(t_node *node)
{
	if (node->job.print)
		free (node->job.print);
	if (node->job.built)
		free (node->job.built);
	if (node->job.path)
		free (node->job.path);
	free(node->job.opt);
	return ;
}

/*Function to set memory and setting fd info for a node*/
void	set_memjob(t_node *node)
{
	node->job.out = STDOUT_FILENO;
	node->job.print = NULL;
	node->job.in = STDIN_FILENO;
	node->job.opt = ft_calloc(1, sizeof(char));
	node->job.path = ft_calloc(1, sizeof(char));
}

/*Control function that return a node structure for processing job*/
t_node	*init_node(t_node *node)
{
	while (node->input[0] != '\0')
	{
		set_memjob(node);
		if (pipe(node->fds) == -1)
			return (NULL);
		parse(node);
		if (node->input[0] == '|')
		{
			node->input++;
			if (node->input[0] == '\0')
				node->err = 1;
		}
		if (node->input[0] != '\0' && node->err == 0)
		{	
			node->next = ft_calloc(1, sizeof(t_node));
			node->next->input = node->input;
			node->next->prev = node;
			node = node->next;
			node->index = node->prev->index + 1;
		}
	}
	return (node);
}

/*Looper function that create a node for each job execution to do*/
t_node	*queue_jobs(t_node *job, char *input)
{
	t_node	*first;
	char	*cmd;
	char	*temp;
	int		i;

	if (!input)
		return (NULL);
	i = 0;
	temp = ft_strdup(input);
	cmd = check_expand(i, temp);
	job = ft_calloc(1, sizeof(t_node));
	job->index = i;
	job->input = cmd;
	job->err = 0;
	first = job;
	while (job->input[0] != '\0')
		job = init_node(job);
	g_data.pipenum = job->index;
	free(cmd);
	return (first);
}

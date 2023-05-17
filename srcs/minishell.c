/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:55 by alvachon          #+#    #+#             */
/*   Updated: 2023/05/16 10:31:51 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	job_process(t_node *process)
{
	t_node	*first;
	int		i;

	i = 0;
	first = process;
	while (i <= g_data.pipenum)
	{
		i++;
		if (builtin_check(process) == 0)
			pipers(process);
		else if (builtin_check(process) != 0)
			exect_cmd(process);
		process = process->next;
	}
	i = 0;
	while (i <= g_data.pipenum)
	{
		close(first->fds[0]);
		close(first->fds[1]);
		free(first);
		first = first->next;
		i++;
	}
	g_data.pipenum = 0;
	return (0);
}

t_node	*shell_process(t_node *process, t_terminal *mini)
{
	while (mini->shell_is_interactive)
	{
		signal(SIGINT, handle_sig);
		display_cmd(mini);
		if (!mini->cmd)
			input_eof();
		if (mini->cmd[0] == '\0' || ft_strcmp(mini->cmd, "\n") == 0 \
			|| ft_isspace(mini->cmd) == 1)
		{
			free(mini->cmd);
			continue ;
		}
		process = queue_jobs(process, mini->cmd);
		add_history(mini->cmd);
		free(mini->cmd);
		g_data.shell_state = SH_READ;
		if (process->next)
			return (process);
		else if (process != NULL)
			exect_cmd(process);
		else if (process == NULL)
			break ;
		free(process);
	}
	return (NULL);
}

int	main(int ac, char **av, char **env)
{
	t_terminal	mini;
	t_node		*process;
	int			i;

	i = 0;
	process = NULL;
	if (ac < 2 && av)
	{
		init_shell(&mini, env);
		while (1)
		{
			process = shell_process(process, &mini);
			if (g_data.pipenum)
				job_process(process);
		}
		return (errno);
	}
	errno = 5;
	return (errno);
}

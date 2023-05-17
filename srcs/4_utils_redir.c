/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_utils_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:03:12 by alvachon          #+#    #+#             */
/*   Updated: 2023/05/16 10:48:53 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Function that trim, read and set data for input token*/
int	do_input(int i, t_node *node)
{
	int		file;
	char	*temp;

	trim_spec(0, node);
	if (token_limit(node->input[0]) == 1 || node->input[0] == '\0')
		return (node->err = 1);
	temp = ft_substr(node->input, 0, wordlen(node->input, i));
	temp = trimchar(temp, 39);
	temp = trimchar(temp, 34);
	node->input = ltrim(node->input);
	file = open(temp, O_RDONLY);
	return (set_file(file, temp, node));
}

char	*do_cmd(char *cmd)
{
	if (cmd != NULL)
		free(cmd);
	cmd = readline("> ");
	if (!cmd)
		input_eof();
	return (cmd);
}

/*Heredoc specific readline set on is own process that return an fd*/
int	sub_readline(char *cmd, char *delim)
{
	int		pipes[2];
	pid_t	child;

	pipe(pipes);
	child = fork();
	while (child == 0)
	{
		cmd = do_cmd(cmd);
		if (ft_strncmp(cmd, delim, ft_strlen(delim)) == 0)
		{
			free(cmd);
			close(pipes[1]);
			exit(0);
		}
		if (cmd[0] == '\0' || ft_strcmp(cmd, "\n") == 0)
			continue ;
		write (pipes[1], cmd, ft_strlen(cmd));
		write (pipes[1], "\n", 1);
	}
	close(pipes[1]);
	free(delim);
	if (child != 0)
		wait(0);
	return (pipes[0]);
}

/*Function that trim, read and set data for heredoc token*/
int	do_heredoc(int i, t_node *node)
{
	char	*delim;
	char	*cmd;
	int		c;

	trim_spec(1, node);
	if (token_limit(node->input[0]) == 1 || node->input[0] == '\0')
		return (node->err = 1);
	c = token_reach(i, node->input);
	if (node->input[0] == '\0' || node->input[0] == '|')
		return (node->err = 2);
	cmd = NULL;
	delim = ft_substr(node->input, 0, c);
	if (ft_isprint(delim[0]) == 0)
		return (2);
	node->input += c - 1;
	return (sub_readline(cmd, delim));
}

/*Function that trim, read and set data for output token*/
int	do_output(int i, t_node *node, int code)
{
	int		file;
	char	*temp;

	file = 0;
	if (node->job.out != STDOUT_FILENO)
		close(node->job.out);
	trim_spec(code, node);
	if (token_limit(node->input[0]) == 1 || node->input[0] == '\0')
		return (node->err = 1);
	temp = subtrim(i, node);
	if (code == 0)
		file = open(temp, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (code == 1)
		file = open(temp, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (file == -1)
	{
		node->job.out = file;
		free(temp);
		return (1);
	}
	node->input = ltrim(node->input);
	node->job.out = file;
	free(temp);
	return (0);
}

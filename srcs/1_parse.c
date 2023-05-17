/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:14:08 by alvachon          #+#    #+#             */
/*   Updated: 2023/05/16 09:02:19 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Control function for heredoc, input, output and append token*/
void	keep_token(int i, t_node *node)
{
	if (ft_strncmp(node->input, "<<", 2) == 0)
		node->job.in = do_heredoc(i, node);
	if (ft_strncmp(node->input, "<", 1) == 0)
		node->err = do_input(i, node);
	if ((ft_strncmp(node->input, ">>", 2) == 0))
		node->err = do_output(i, node, 1);
	else if (ft_strncmp(node->input, ">", 1) == 0)
		node->err = do_output(i, node, 0);
	else
		node->input++;
}

/*Control function for elements printable on terminal*/
void	keep_print(int i, t_node *node)
{
	int	j;

	j = 1;
	while (ft_strncmp(node->job.built, "echo", 4) == 0 && \
		ft_strncmp(node->input, "-n", 2) == 0)
	{
		while (node->input[j + 1] != '\0' && node->input[j + 1] == 'n')
			j++;
		if (node->input[j + 1] != ' ' && node->input[j + 1] != '\0')
			break ;
		free(node->job.opt);
		node->job.opt = ft_strdup("-n");
		node->input = wordtrim(node->input, wordlen(node->input, i));
		node->input = ltrim(node->input);
	}
	if (!node->job.print)
	{
		while (node->input && token_limit(node->input[0]) == 0)
		{
			if (node->input[0] == 34 || node->input[0] == 39)
				do_guil(node, i);
			else
				do_sp(node, i);
		}
	}
}

/*Control function for cd option directory*/
void	keep_option(t_node *node)
{
	node->job.temp = node->job.print;
	if (node->job.temp == NULL && ft_strncmp(node->job.built, "cd", 2) == 0)
		node->job.temp = "home";
	if (ft_strcmp(node->job.built, "cd") == 0)
	{
		if (ft_strncmp(node->job.temp, "home", 4) == 0)
			do_home_path(node);
		else if (ft_strncmp(node->job.temp, "/", 1) != 0)
			do_relative_path(node);
		if (ft_strncmp(node->job.temp, ".", 1) == 0)
			node->job.temp++;
		if (ft_strncmp(node->job.temp, "/", 1) == 0)
			do_direct_path(node);
	}
}

/*Control function to keep the builtin in the struct*/
void	keep_builtin(int i, t_node *node)
{
	char	*str;

	node->input = ltrim(node->input);
	i = token_reach(i, node->input);
	str = ft_substr(node->input, 0, i);
	if (ft_strncmp(str, "ECHO", 5) == 0)
		str = ulstr(str);
	node->job.built = ft_strdup(str);
	free(str);
	node->input = wordtrim(node->input, i);
	node->input = ltrim(node->input);
}

/*Function that parse and keep elements for the execution for each nodes
* (pipe separated) */
void	parse(t_node *node)
{
	int	i;

	i = 0;
	keep_builtin(i, node);
	keep_print(i, node);
	keep_option(node);
	while (node->input[0] != '\0' && node->input[0] != '|')
		keep_token(i, node);
	if (node->err > 0)
		data_free(node);
}

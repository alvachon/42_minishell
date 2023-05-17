/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:22:05 by alvachon          #+#    #+#             */
/*   Updated: 2023/05/10 15:15:17 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	scan_for_word(char *input)
{
	int	i;

	i = 0;
	while (input[i] && input[i] == 32)
		i++;
	if (input[i] == '|')
		return (0);
	if (input[i] == '<')
		return (0);
	if (input[i] == '>')
		return (0);
	if (ft_isprint(input[i]) == 1 && input[i] != 32)
		return (1);
	return (2);
}

char	*add_content(char *content, char *add, int position, char *var)
{
	char	*mod;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	mod = ft_calloc(1, (ft_strlen(content)) + ft_strlen(add));
	while (i != position)
	{
		mod[i] = content[i];
		i++;
	}
	k = i;
	while (add[j])
		mod[i++] = add[j++];
	j = ft_strlen(var) + k;
	while (k < j)
		k++;
	while (content[k])
		mod[i++] = content[k++];
	mod[i] = '\0';
	free(content);
	return (mod);
}

void	do_guil(t_node *node, int i)
{
	char	c;
	char	*sub;

	c = node->input[0];
	node->input++;
	i = chartrim(node->input, c);
	if (i == 0)
	{
		node->input++;
		return ;
	}
	if (i > 0)
	{
		sub = ft_substr(node->input, 0, i);
		if (node->job.print == NULL)
			node->job.print = ft_strdup(sub);
		else
			node->job.print = ft_strpaste(node->job.print, sub);
		free(sub);
	}
	else
		node->job.print = ft_calloc(1, sizeof(char));
	while (i-- + 1)
		node->input++;
}

void	do_sp(t_node *node, int i)
{
	char	*sub;

	i = token_reach(i, node->input);
	if (i > 0)
	{
		sub = ft_substr(node->input, 0, i);
		if (node->job.print == NULL)
			node->job.print = ft_strdup(sub);
		else
			node->job.print = ft_strpaste(node->job.print, sub);
		free(sub);
	}
	else if (node->input && i == 0 && node->input[i] == ' ')
	{
		while (*node->input == ' ' && ft_isalnum(node->input[1]) == 0)
			node->input++;
		if (scan_for_word(node->input) == 1 && node->job.print != NULL)
			node->job.print = ft_strpaste(node->job.print, " ");
		node->input = ltrim(node->input);
	}
	else
		node->job.print = ft_calloc(1, sizeof(char));
	while (*node->input && i--)
		node->input++;
}

int	z_echo(t_cmd data, char **env)
{
	int		i;
	char	c;

	i = 0;
	c = '\n';
	(void)env;
	if (ft_strncmp(data.opt, "-n", 2) == 0)
	{
		while (data.print && data.print[i] != '\0')
		{
			write(data.out, &data.print[i], 1);
			i++;
		}	
	}
	else
	{
		while (data.print && data.print[i] != '\0')
		{
			write(data.out, &data.print[i], 1);
			i++;
		}
		if (errno != 2)
			write (data.out, &c, 1);
	}
	return (errno);
}

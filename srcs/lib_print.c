/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:27:43 by alvachon          #+#    #+#             */
/*   Updated: 2023/05/16 09:50:07 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Find a specific ascii char as trigger system*/
int	scan(char *input, char c)
{
	int	i;

	i = 0;
	if (!input)
		return (1);
	while (input[i])
	{
		if (input[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	skip_simple_guil(int i, char *input)
{
	i++;
	while (input[i] != 39 && input[i] != '\0')
		i++;
	if (input[i] == 39)
		i++;
	return (i);
}

/*
Return a strlen until a specific reach */
int	chartrim(char *input, char c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(input);
	if (scan(input, c) == 1)
		return (len);
	while (input[i] != c && input[i] != '\0')
	{
		i++;
		len--;
	}
	return (i);
}

int	token_limit(char c)
{
	if (!c)
		return (1);
	if (c == '<')
		return (1);
	if (c == '>')
		return (1);
	if (c == '|')
		return (1);
	if (c == '\0')
		return (1);
	return (0);
}

/*
Return the closest len based on token reaching*/
int	token_reach(int i, char *str)
{
	if (!str)
		return (0);
	i = chartrim(str, 34);
	if (i > chartrim(str, ' '))
		i = chartrim(str, ' ');
	if (i > chartrim(str, 39))
		i = chartrim(str, 39);
	if (i > chartrim(str, '|'))
		i = chartrim(str, '|');
	if (i > chartrim(str, '<'))
		i = chartrim(str, '<');
	if (i > chartrim(str, '>'))
		i = chartrim(str, '>');
	return (i);
}

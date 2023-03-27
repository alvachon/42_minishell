/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:27:43 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/26 19:13:33 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 Calc the size of str until a clear ascii like ' ' */
int	wordlen(char *input, int i)
{
	while (input[i] > 32)
		i++;
	return (i);
}

/*
 Clear a word that have been parsed */
char	*wordtrim(char *input, int i)
{
	while (i >= 0)
	{
		input++;
		i--;
	}
	return (input);
}

/*
Calc how many words in the input*/
int	wordcount(char *str)
{
	int	w;
	int	c;

	w = 0;
	c = 0;
	while (*str)
	{
		if (*str > 32)
		{
			w = 1;
			while (*str > 32)
				str++;
		}
		if (*str <= 32 && w == 0)
		{
			while (*str <= 32)
				str++;
		}
		if (*str <= 32 && w == 1)
		{
			c += w;
			w = 0;
		}
	}
	printf("%d\n", c);
	return (c);
}

/*
Find a specific ascii char as trigger system*/
int	scan(char *input, char c)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == c)
			return (0);
		i++;
	}
	return (1);
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

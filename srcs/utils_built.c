/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_built.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:17:01 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/05 19:57:16 by alvachon         ###   ########.fr       */
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
 Trim clear ascii like ' ' on LEFT */
char	*ltrim(char *input)
{
	while (*input <= 32 && *input !='\0')
		input++;
	return (input);
}

/*
 Clear a word that have been parsed */
char	*wordtrim(char *input, int i)
{
	while (i >= 0 && *input != '\0')
	{
		input++;
		i--;
	}
	return (input);
}

/*
 Transform MAJ input into small input */
char	*ulstr(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += ' ';
		i++;
	}
	return (str);
}

/*
Versatile function to delete a specifique character of the input*/
char	*trimchar(char *file, char c)
{
	int		i;
	int		j;
	char	*copy;

	i = 0;
	j = 0;
	copy = file;
	while (file[i])
	{
		if (file[i] == c)
			i++;
		copy[j] = file[i];
		i++;
		j++;
	}
	copy[j] = '\0';
	return (copy);
}

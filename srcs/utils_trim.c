/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/23 14:42:59 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/23 15:37:03 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
 Trim clear ascii like ' ' on LEFT */
char	*ltrim(char *input)
{
	while (*input <= 32)
		input++;
	return (input);
}

/*
 Trim clear ascii like ' ' on RIGHT */
char	*rtrim(char *str)
{
	int	i;
	int	j;

	j = -1;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] > 32)
			j = i;
		i++;
	}
	str[j + 1] = '\0';
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

/*
1. Function to trim " " ou ' ' with their own specification*/
void	trim_guil(t_cmd **data, char c, int trig)
{
	char	*file;

	file = scan_end((**data).input, trig);
	if (trig == 1)
	{
		file = trimchar(file, 34);
		file = trimchar(file, 39);
	}
	if (scan(file, 34) == 1)
	{
		if (scan(file, 39) == 1)
		{
			(**data).print = file;
			return ;
		}
	}
	if (trig == 0)
		(**data).print = trimchar(file, c);
}


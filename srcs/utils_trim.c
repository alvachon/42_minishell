/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_trim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:26:22 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/29 14:35:24 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
1. Function to trim " " ou ' ' with their own specification*/
void	trim_guil(t_cmd *data, char c)
{
	char	*file;
	int		i;

	file = data->input;
	i = 0;
	if (file[i] == c)
	{
		i++;
		while (file[i] != c)
			i++;
	}
	else
	{
		while (file[i] != c || file[i] != '\0')
			i++;
	}
	data->print = file;
	printf("%s\n", data->print);
	data->print[i] = '\0';
	while (i)
	{
		data->input++;
		i--;
	}
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

int	len_until_trigger(char *file, char c, int j)
{
	int i;

	i = 0;
	while (j > 0)
	{
		if (file[i] == c)
			j--;
		i++;
	}
	return (i);
}
/*
Versatile function to delete a specifique character of the input*/
int	sizebetweenchar(char *file, char c)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (file[i])
	{
		if (file[i] == c)
			j++;
		i++;
	}
	return (j);
}

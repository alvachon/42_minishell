/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:17:01 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/22 14:35:44 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
! Deplace the function into .c for utils_parser [ ]
 Trim clear ascii like ' ' on LEFT */
char	*ltrim(char *input)
{
	while (*input <= 32)
		input++;
	return (input);
}

/*
! Deplace the function into .c for utils_parser [ ]
 Calc the size of str until a clear ascii like ' ' */
int	wordlen(char *input, int i)
{
	while (input[i] > 32)
		i++;
	return (i);
}

/*
! Deplace the function into .c for utils_parser [ ]
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
! Deplace the function into .c for utils_parser [ ]
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
 Work only for echo (hardcode option for -n)*/
void	keep_option(int i, t_cmd *data)
{
	if ((*data).input[0] == '-' && (*data).input[1] == 'n'
		&& (*data).input[2] <= 32)
	{
		(*data).opt = ft_substr((*data).input, 0, 2);
		i = 2;
		(*data).input = wordtrim((*data).input, i);
		(*data).input = ltrim((*data).input);
	}
}

/*
! Regroup all keep_builtin together [ ]
! Call of ulstr not called if other char ar in MAJ ... Need better call[ ]
! Test trimchar edgecase from this call [ ]
! Check if better trimchar or rtrim (parse_print.c) [ ]
 1. Trim clear character until printable
 2. Take the size of the word
 3. Separate the word from the rest of the string
 4. if the string at postion [0] is in maj,
	check to put everything in minuscule !
 5. I use trimchar but I dont remember why
 6. Put the parse data in the struct.
 7. Trim the word
 8. Trim clear character for next input.
 */
void	keep_builtin(int i, t_cmd *data)
{
	char	*str;

	(*data).input = ltrim((*data).input);
	i = wordlen((*data).input, i);
	str = ft_substr((*data).input, 0, i);
	if (str[0] >= 'A' && str[0] <= 'Z')
		str = ulstr(str);
	str = trimchar(str, 32);
	(*data).built = str;
	(*data).input = wordtrim((*data).input, i);
	(*data).input = ltrim((*data).input);
}

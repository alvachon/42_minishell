/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:17:01 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/24 16:36:53 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
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

/*Po sur pentoute*/
int	move_info(char *str)
{
	int	i;

	i = 0;
	while (*str == '.' || *str == '/')
			i++;
	return (i);
}

/*
 Work only for echo (hardcode option for -n)
 Also used for cd .. or .*/
void	keep_option(int i, t_cmd *data)
{
	/*if (strcmp("cd", data->built) == 0) ps bon
	{
		if ((*data).input[0] == '.' && (*data).input[1] != '.')
			(*data).opt = g_data.pwd;
		else if ((*data).input[0] == '~' || (*data).input[0] <= 32)
			(*data).opt = g_data.home;
		else if ((*data).input[0] == '.' && (*data).input[1] == '.')
			(*data).opt = g_data.pwd;// a changer
	}*/
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
! Test edge case condition [ ]
 1. If not < > | , enter the function
 2. Check the guillemet type and do the trim in consequence
	(Keep the data in the struct)
 3. Take the len of the input and clear the data in the str*/
void	keep_print(int i, t_cmd *data)
{
	if ((*data).input[0] != '<' || (*data).input[0] != '>'
		|| (*data).input[0] != '|')
	{
		if ((*data).input[0] == 34)
			trim_guil(&data, 34, 0);
		else if ((*data).input[0] == 39)
			trim_guil(&data, 39, 0);
		else
			trim_guil(&data, 0, 1);
	}
	i = ft_strlen((*data).print);
	while (i)
	{
		(*data).input++;
		i--;
	}
}

/*
! Need a new keep to put all the ./../ situation and maybe < or > ... ? [ ]
 1. Keep builtin and keep_option is in parse_builtin.c
 2. Keep print is in parse_print.c */
t_cmd	parse(t_cmd data)
{
	int	i;

	i = 0;
	while (1)
	{
		keep_builtin(i, &data);
		keep_option(i, &data);
		keep_print(i, &data);
		/*input = keep_redir_input(input, i);
		input = keep_flag_delim(input, i);
		//input = keep_delimiter(input, i);
		printf("parse : %s\n", input);*/
		return (data);
	}
}

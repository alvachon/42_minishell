/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:17:01 by alvachon          #+#    #+#             */
/*   Updated: 2023/02/23 15:17:03 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char *ltrim(char *input)
{
	while (*input <= 32)
		input++;
	return (input);
}

int	wordlen(char *input, int i)
{
	while (input[i] > 32)
		i++;
	return (i);
}

char *wordtrim(char *input, int i)
{
	while (i >= 0)
	{
		input++;
		i--;
	}
	return (input);
}

char *ulstr(char *str)
{
	int i;

	i = 0;
  	while (str[i])
  	{
    	if (str[i] >= 'A' && str[i] <= 'Z')
      		str[i] += ' ';
    i++;
  }
	return (str);
}

char *keep_option(char *input, int i)
{
	if (input[0] == '-' && input[1] == 'n' && input[2] <= 32)
	{
		g_data.input.opt = ft_substr(input, 0, 2);
		i = 2;
		input = wordtrim(input, i);
		input = ltrim(input);
	}
	return (input);
}

char *keep_builtin(char *input, int i)
{
	char *str;
	input = ltrim(input);
	i = wordlen(input, i);
	str = ft_substr(input, 0, i);
	/*if (str[0] >= 'A' && str[0] <= 'Z')
		str = ulstr(str);*/
	g_data.input.built = str;
	input = wordtrim(input, i);
	input = ltrim(input);
	return (input);
}
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

void	keep_option(int i, t_cmd *data)
{
	if ((*data).input[0] == '-' && (*data).input[1] == 'n' && (*data).input[2] <= 32)
	{
		(*data).opt = ft_substr((*data).input, 0, 2);
		i = 2;
		(*data).input = wordtrim((*data).input, i);
		(*data).input = ltrim((*data).input);
	}
}

void	keep_builtin(int i, t_cmd *data)
{
	char *str;
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
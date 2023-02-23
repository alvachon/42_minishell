/*/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:20:24 by alvachon          #+#    #+#             */
/*   Updated: 2023/02/23 15:20:26 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int scan(char *input, char c)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == c)
			return (0);
		i++;
	}
	return (1);
}

int	chartrim(char *input, char c)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(input);
	if (scan(input, c) == 1)
		return (len);
	while (input[i] != c)
	{
		i++;
		len--;
	}
	return (i);
}

char *rtrim(char *str)
{
	int i;
	int j;

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

char *scan_end(char *file)
{
	char **cmd;

	if (scan(file, '<') == 0)
	{
		cmd = ft_split(file, '<');
		file = cmd[0];
		free (cmd);
	}
	if (scan(file, '>') == 0)
	{
		cmd = ft_split(file, '>');
		file = cmd[0];
		free (cmd);
	}
	if (scan(file, '|') == 0)
	{
		cmd = ft_split(file, '>');
		file = cmd[0];
		free (cmd);
	}
	return (file);
}

void	trim_guil(char *input, char c)
{
	char 	**cmd;
	char 	*file;
	int		len_word;
	int		trig;

	trig = 1;
	if (input[0] == c)
	{
		input++;
		trig = 0;
	}
	while (*input)
	{
		cmd = ft_split(input, c);
		file = cmd[0];
		if (g_data.input.print == NULL)
			g_data.input.print = file;
		else
			g_data.input.print = ft_strjoin(g_data.input.print, file);
		if (trig == 1)
			g_data.input.print = scan_end(g_data.input.print);
		g_data.input.print = rtrim(g_data.input.print);
		if (trig == 1)
		{
			len_word = chartrim(input, c);
			while (len_word >= 0)
			{
				input++;
				len_word--;
			}
		}
		free (cmd);
	}
}

char	*keep_print(char *input, int i)
{
	(void)i;
	char *copy;
	if (input[0] != '<' || input[0] != '>' || input[0] != '|')
	{
		if (input[0] == 34)//"
		{
			trim_guil(input, 34);
		}
		else if (input[0] == 39)//'
		{
			trim_guil(input, 39);
		}
		else
		{
			trim_guil(input, 34);
			copy = g_data.input.print;
			g_data.input.print = NULL;
			trim_guil(copy, 39);
		}
	}
	while (*input)
	{
		if (*input == '<' || *input == '>' || *input == '|')
			break ;
		input++;
	}
	//trim aussi le input pour enlever ce qui a apres les flags
	//g_data.input.print = rtrim(g_data.input.print) implementer enlever espace de fin
	return (input);
}
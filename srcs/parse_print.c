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
	while (input[i] != c && input[i] != '\0')
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

void	trim_guil(t_cmd **data, char c)
{
	char 	**cmd;
	char 	*file;
	int		len_word;
	int		trig;

	trig = 1;
	if ((**data).input[0] == c)
	{
		(**data).input++;
		trig = 0;
	}
	cmd = ft_split((**data).input, c);
	file = cmd[0];
	(**data).print = file;
	if (trig == 1)
		(**data).print = scan_end((**data).print);
	(**data).print = rtrim((**data).print);
	if (trig == 1)
	{
		len_word = chartrim((**data).input, c);
		if ((**data).input[len_word] == '\0')
			return ;
		else
		{
			while (len_word >= 0)
			{
				(**data).input++;
				len_word--;
			}
		}
	}
	free (cmd);
}

void	keep_print(int i, t_cmd *data)
{
	(void)i;
	if ((*data).input[0] != '<' || (*data).input[0] != '>' || (*data).input[0] != '|')
	{
		if ((*data).input[0] == 34)//"
		{
			trim_guil(&data, 34);
		}
		else if ((*data).input[0] == 39)//'
		{
			trim_guil(&data, 39);
		}
		else
		{
			trim_guil(&data, 34);
			trim_guil(&data, 39);
		}
	}
	while (*(*data).input)
	{

		if (*(*data).input == '<' || *(*data).input == '>' || *(*data).input == '|')
			break ;
		(*data).input++;
	}
	//trim aussi le input pour enlever ce qui a apres les flags
	//g_(*data).input.print = rtrim(g_(*data).input.print) implementer enlever espace de fin
}
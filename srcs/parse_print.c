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

char *scan_end(char *file)//ne pas changer important
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


int		wordcount(char *str)
{
	int w = 0;
	int c = 0;
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

char *delguil(char *file, char c)
{
	int 	i;
	int		j;
	char *copy;

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

void	trim_guil(t_cmd **data, char c)//trig
{
	char 	**cmd;
	char 	*file;
	int		word;
	int		i;
	int		trig;

	trig = 1;//when no guillemet
	if ((**data).input[0] == c)//if guill type
	{
		printf("guil\n");
		trig = 0;
	}
	i = 1;
	file = scan_end((**data).input);
	word = wordcount(file);
	if (trig == 1)
	{
		file = delguil(file, 34);
		file = delguil(file, 39);
	}
	if (scan(file, 34) == 1)
	{
		if (scan(file, 39) == 1)
		{
			(**data).print = file;
			return ;
		}
	}
	cmd = ft_split((**data).input, c);
	file = cmd[0];
	word -= 1;
	printf("char split = %c\n", c);
	printf("cmd[0] = %s\n", cmd[0]);
	printf("cmd[1] = %s\n", cmd[1]);
	while (word)
	{
		file = ft_strjoin(file, cmd[i]);
		i++;
		word--;
		printf("%s\n", file);
		exit (1);
	}
	printf("%s\n", file);
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

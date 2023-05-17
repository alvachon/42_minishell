/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_readline.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:46:03 by alvachon          #+#    #+#             */
/*   Updated: 2023/05/16 10:38:21 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	isallnum(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (2);
	while (str[i] != '\0')
	{
		if (i == 0 && (str[i] == '+' || str[i] == '-'))
		{
			i++;
			continue ;
		}
		if (str[i] != '\0' && ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	check_buffer(int buf_siz, char **buf, int str_siz)
{
	if (!buf_siz)
		return (0);
	buf_siz += buf_siz;
	buf = ft_realloc(buf, buf_siz);
	str_siz = buf_siz;
	return (str_siz);
}

int	check_end(int fd, int buf_siz, char **buf)
{
	int	ch;

	ch = ft_getchar(fd);
	if (ch == EOF)
	{
		if (buf_siz)
			free(buf);
		return ('\0');
	}
	return (ch);
}

char	*check_delim(int trigger, int i, char *buf, char *delim)
{
	char	*buff;

	if (trigger == 2)
	{
		i = ft_stristr(buf, delim, ft_strlen(buf));
		if (i != 0)
		{
			buff = ft_substr(buf, 0, i);
			return (buff);
		}
		return (buf);
	}
	return (buf);
}

char	*ft_readline(int fd, int trigger, char *delim)
{
	char	*buf;
	int		i;
	int		buf_siz;
	int		str_siz;

	i = 0;
	buf_siz = 64;
	buf = ft_calloc(1, buf_siz);
	str_siz = buf_siz;
	while (1)
	{
		if (i == str_siz - 1)
		{
			str_siz = check_buffer(buf_siz, &buf, str_siz);
			if (str_siz == 0)
				break ;
		}
		buf[i] = check_end(fd, buf_siz, &buf);
		if (buf[i] == '\n' || buf[i] == '\0')
			break ;
		i++;
	}
	buf[i] = '\0';
	buf = check_delim(trigger, i, buf, delim);
	return (buf);
}

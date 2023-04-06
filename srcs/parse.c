/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:14:08 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/06 11:51:11 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
1. IN DIR (pwd) -> find file test.txt
	if YES -> READ
	if NO -> return error
2. READ -> Take full size, put in print.
3. while word(input), input++;

cd < test.txt "/Users/alvachon" WORK

echo < test.txt BLANK

a=5
export < test.txt "a" WORK

a=5
unset < test.txt "a" WORK

env < test.txt WORK (rien de special)
pwd < test.txt WORK (rien de special)
exit < test.txt WORK (rien de special)
*/

int	ft_getchar(int fd)
{
	char	buf[BUFSIZ];
	char	*bufptr;
	int		i;

	bufptr = buf;
	i = 0;
	if (i == 0)
	{
		i = read(fd, buf, 1);
		bufptr = buf;
	}
	if (--i >= 0)
		return (*bufptr++);
	return (0);
}

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new;

	if (!ptr)
	{
		new = malloc(size);
		if (!new)
			return (NULL);
	}
	else
	{
		if (sizeof(ptr) < size)
		{
			new = malloc(size);
			if (!new)
				return (NULL);
			ft_memcpy(new, ptr, sizeof(ptr));
			free(ptr);
		}
		else
			new = ptr;
	}
	return (new);
}

char	*ft_readline(int fd)
{
	int		buf_siz;
	int		str_siz;
	char	*buf;
	int		ix;
	int		ch;

	ix = 0;
	buf_siz = 64;
	buf = malloc(buf_siz);
	str_siz = buf_siz;
	while (1)
	{
		if (ix == str_siz - 1)
		{
			if (!buf_siz)
				break ;
			buf_siz += buf_siz;
			buf = ft_realloc(buf, buf_siz);
			str_siz = buf_siz;
		}
		ch = ft_getchar(fd);
		if (ch == EOF)
		{
			if (buf_siz)
				free(buf);
			return (NULL);
		}
		if (ch == '\n')
			break ;
		buf[ix] = ch;
		ix++;
	}
	buf[ix] = '\0';
	return (buf);
}

void	keep_redir_input(int i, t_cmd *data)
{
	char	*file;
	char	*read;
	int		fd;

	if (data->input[0] == '<' && data->input[1] <= 32)
	{
		data->redir_input = ft_substr(data->input, 0, 1);
		data->input++;
		ltrim(data->input);
			data->input = ltrim(data->input);
		file = ft_substr(data->input, 0, wordlen(data->input, i));
		fd = open(file, O_RDONLY);
		if (fd == -1)
			return ;//
		read = ft_readline(fd);
		printf("%s\n", read);
		close(fd);
	}
	if (data->input[0] == '<' && data->input[1] == '<')
	{
		data->flag_delim = ft_substr(data->input, 0, 2);
		data->input += 2;
	}
}

void	keep_flag_delim(t_cmd *data, int i)
{
	if (data->input[0] == '<' && data->input[1] == '<')
	{
		data->flag_delim = ft_substr(data->input, 0, 2);
		i = 2;
		data->input = wordtrim(data->input, i);
		ltrim(data->input);
	}
}

void	keep_print(int i, t_cmd *data)
{
	if (data->input[0] == 34 || data->input[0] == 39)
		do_guil(data, i);
	else
		do_sp(data, i);
	while (scan(data->print, '$') == 0)
		do_ref(data, i);
}

void	keep_option(t_cmd *data)
{
	if (strcmp(data->built, "echo") == 0 && strncmp(data->input, "-n ", 3) == 0)
	{
		data->opt = "-n";
		data->input = wordtrim(data->input, 2);
		data->input = ltrim(data->input);
	}
	if (strcmp(data->built, "cd") == 0)
	{
		if (strncmp(data->input, "/", 1) != 0)
			do_relative_path(data);
		if (strncmp(data->input, ".", 1) == 0)
			data->input++;
		if (strncmp(data->input, "/", 1) == 0)
			do_direct_path(data);
	}
}

void	keep_builtin(int i, t_cmd *data)
{
	char	*str;

	data->input = ltrim(data->input);
	i = wordlen(data->input, i);
	str = ft_substr(data->input, 0, i);
	str = ulstr(str); //echo seulement
	str = trimchar(str, 32);
	data->built = ft_strdup(str);
	free(str);
	data->input = wordtrim(data->input, i);
	data->input = ltrim(data->input);
}

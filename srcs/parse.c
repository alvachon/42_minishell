/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:14:08 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/11 13:48:38 by alvachon         ###   ########.fr       */
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

int	ft_stristr(const char *haystack, const char *needle, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (needle[i] == '\0')
		return (0);
	while (i < len && haystack[i] != '\0')
	{
		j = 0;
		while ((haystack[i + j] == needle[j]) && ((i + j) < len))
		{
			j++;
			if (j == ft_strlen(needle))
				return (i);
		}
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
	int		ch;

	ch = ft_getchar(fd);
	if (ch == EOF)
	{
		if (buf_siz)
			free(buf);
		return ('\0');
	}
	return (ch);
}

char *check_delim(int trigger, int i, char *buf, char *delim)
{
	char *buff;

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

//rendu la rapetisser la fonction
char	*ft_readline(int fd, int trigger, char *delim)
{
	char	*buf;
	int		i;
	int		buf_siz;
	int		str_siz;

	i = 0;
	buf_siz = 64;
	buf = malloc(buf_siz);
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
	printf("%s\n", buf);
	return (buf);
}

/*po sur pour read doc ...*/
void	keep_redir_input(int i, t_cmd *data)
{
	char	*read;
	char	*delim;
	int		fd;
	int		t;

	t = 0;
	delim = NULL;
	if (data->input[0] == '<' && data->input[1] <= 32)
	{
		data->input++;
		t = 1;
	}
	if (t > 0)
	{
		data->input = ltrim(data->input);
		fd = open(ft_substr(data->input, 0, wordlen(data->input, i)), O_RDONLY);
		if (fd == -1)
			return ;//
		while (data->input[0] > 32)
			data->input++;
		data->input = ltrim(data->input);
		printf("%s\n", data->input);
		if (data->input[0] == '<' && data->input[1] == '<')
		{
			printf("yey\n");
			data->input += 2;
			t = 2;
			data->input = ltrim(data->input);
			printf("%s\n", data->input);
			delim = ft_substr(data->input, 0, wordlen(data->input, i));
			printf("%s\n", delim);
		}
		read = ft_readline(fd, t, delim);
		if (ft_strcmp(data->built, "cd") == 0)
			data->path = read;
		else
			data->print = read;
		close(fd);
		data->input = ltrim(data->input);
	}
}


void	keep_print(int i, t_cmd *data)
{
	if (data->input[0] == 34 || data->input[0] == 39)
		do_guil(data, i);
	else
		do_sp(data, i);//
	while (scan(data->print, '$') == 0)
		do_ref(data, i);
}

void	keep_option(t_cmd *data)
{
	/*if (strcmp(data->built, "echo") == 0 && strncmp(data->input, "-n ", 3) == 0)
	{
		data->opt = "-n";
		data->input = wordtrim(data->input, 2);
		data->input = ltrim(data->input);
	}*/
	if (strcmp(data->built, "cd") == 0)
	{
		if (strncmp(data->print, "/", 1) != 0)
			do_relative_path(data);
		if (strncmp(data->print, ".", 1) == 0)
			data->print++;
		if (strncmp(data->print, "/", 1) == 0)
			do_direct_path(data);
	}
}

void	keep_builtin(int i, t_cmd *data)
{
	char	*str;

	data->input = ltrim(data->input);
	i = wordlen(data->input, i);
	str = ft_substr(data->input, 0, i);
	if (ft_strncmp(str, "ECHO", 5) == 0)
		str = ulstr(str);
	str = trimchar(str, 32);
	data->built = ft_strdup(str);
	free(str);
	data->input = wordtrim(data->input, i);
	data->input = ltrim(data->input);
}

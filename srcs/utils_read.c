/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 14:47:54 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/11 14:49:06 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

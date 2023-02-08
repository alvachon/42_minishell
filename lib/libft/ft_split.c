/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <fboulang@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 08:58:52 by fboulang          #+#    #+#             */
/*   Updated: 2022/04/04 08:58:55 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <string.h>

static unsigned int	ft_count(char const *s, char c);
static unsigned int	ft_copy(char *temp, char const *s, char c, unsigned int i);

static int	word(char const *s, char c, int i)
{
	int	len;

	len = 1;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

static unsigned int	ft_copy(char *temp, char const *s, char c, unsigned int i)
{
	unsigned int	j;

	j = 0;
	while (s[i] != c && i < ft_strlen(s))
	{
		temp[j] = s[i];
		i++;
		j++;
	}
	if (j == 0)
		temp = NULL;
	return (i);
}

static unsigned int	ft_count(char const *s, char c)
{
	unsigned int	i;
	int				count;

	i = 0;
	count = 0;
	while (s[i] == c)
		i++;
	if (i == ft_strlen(s))
		return (count);
	while (s[i])
	{
		if ((s[i] == c && s[i + 1] != c) || (s[i + 1] == '\0' && s[i] != c))
			count++;
		i++;
	}
	return (count);
}

static char	**safeguard(char **a)
{
	a = ft_calloc(1, sizeof(char *));
	return (a);
}

char	**ft_split(char const *s, char c)
{
	char			**a;
	char			*temp;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	a = NULL;
	if (s == NULL || s[0] == '\0')
		return (safeguard(a));
	a = ft_calloc(ft_count(s, c) + 1, sizeof(char *));
	if (!a)
		return (NULL);
	while (j < (ft_count(s, c)) && s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		temp = ft_calloc(word(s, c, i), sizeof(char));
		i = ft_copy(temp, s, c, i);
		a[j] = temp;
		while (s[i] == c)
			i++;
		j++;
	}
	return (a);
}

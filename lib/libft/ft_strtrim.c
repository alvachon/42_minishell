/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <fboulang@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 10:27:11 by fboulang          #+#    #+#             */
/*   Updated: 2022/04/01 10:27:14 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static int	ft_favori(const char *s1, const char *set);
static int	ft_neckbeard(const char *s1, const char *set);

int	ft_favori(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (set[j] != '\0' && s1[i] != '\0')
	{
		j = 0;
		while (s1[i] != set[j] && set[j] != '\0')
			j++;
		if (s1[i] == set[j])
			i++;
	}
	return (i);
}

int	ft_neckbeard(const char *s1, const char *set)
{
	int	j;
	int	k;

	j = 0;
	k = (int)ft_strlen(s1) - 1;
	while (set[j] != '\0' && k > 0)
	{
		j = 0;
		while (s1[k] != set[j] && set[j] != '\0')
			j++;
		if (set[j] == s1[k])
			k--;
	}
	return (k);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char			*a;
	int				dodge;

	a = NULL;
	if (!s1)
		return (NULL);
	if (ft_neckbeard(s1, set) == 0 || ft_favori(s1, set) == (int)ft_strlen(s1))
	{			
		a = ft_calloc(1, sizeof(char));
		a[0] = '\0';
		return (a);
	}
	dodge = (ft_neckbeard(s1, set) - ft_favori(s1, set)) + 1;
	a = ft_substr(s1, ft_favori(s1, set), dodge);
	if (!a)
		return (NULL);
	else
		return (a);
}

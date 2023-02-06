/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <fboulang@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 08:48:30 by fboulang          #+#    #+#             */
/*   Updated: 2022/04/01 08:48:34 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*a;
	unsigned int	i;

	i = 0;
	if (!s)
		return (NULL);
	if (start == 0 && len > ft_strlen(s))
		a = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	else if (start > ft_strlen(s) && len > ft_strlen(s))
		a = ft_calloc(1, sizeof(char));
	else
		a = ft_calloc (len + 1, sizeof(char));
	if (len <= 0)
		return (a);
	if (!a)
		return (NULL);
	while (len && s[start + i] != '\0' && start <= ft_strlen(s))
	{
		a[i] = s[start + i];
		i++;
		len--;
	}
	return (a);
}

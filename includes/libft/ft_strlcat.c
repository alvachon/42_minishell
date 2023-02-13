/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <fboulang@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:17:21 by fboulang          #+#    #+#             */
/*   Updated: 2022/03/29 14:17:23 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	k;
	size_t	l;

	j = 0;
	i = ft_strlen(dst);
	k = i;
	l = ft_strlen(src);
	if (k > dstsize)
		return (dstsize + l);
	if (k < dstsize)
	{
		while (j < (dstsize - k - 1) && src[j] != '\0')
		{
			dst[i + j] = src [j];
			j++;
		}
	}
	dst[i + j] = '\0';
	return (k + l);
}

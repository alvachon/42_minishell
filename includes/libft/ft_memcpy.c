/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <fboulang@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:19:59 by fboulang          #+#    #+#             */
/*   Updated: 2022/03/29 10:20:03 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int		i;
	char	*a;

	i = 0;
	a = (char *) dst;
	if (!src && !dst)
		return (NULL);
	while (n)
	{
		a[i] = ((char *)src)[i];
		i++;
		n--;
	}
	return (dst);
}

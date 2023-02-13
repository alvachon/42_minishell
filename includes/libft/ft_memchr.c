/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <fboulang@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:27:19 by fboulang          #+#    #+#             */
/*   Updated: 2022/03/30 11:27:22 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*temp;
	int				i;

	i = 0;
	temp = (unsigned char *) s;
	while (n)
	{
		if (temp[i] == (unsigned char)c)
			return ((void *) &s[i]);
		i++;
		n--;
	}
	return (NULL);
}

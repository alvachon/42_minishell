/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <fboulang@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 11:36:43 by fboulang          #+#    #+#             */
/*   Updated: 2022/03/30 11:36:46 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*temp;
	unsigned char	*temp2;
	unsigned int	i;

	i = 0;
	temp = (unsigned char *) s1;
	temp2 = (unsigned char *) s2;
	if (n == 0)
		return (0);
	while (i < n)
	{
		if (temp[i] != temp2[i])
			return (temp[i] - temp2[i]);
		i++;
	}
	return (0);
}

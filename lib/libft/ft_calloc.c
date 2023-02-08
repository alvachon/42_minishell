/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <fboulang@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:22:09 by fboulang          #+#    #+#             */
/*   Updated: 2022/03/30 13:22:13 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc (count * size);
	if (count == SIZE_MAX && size == SIZE_MAX)
		return (NULL);
	if (!ptr)
		return (NULL);
	ft_memset (ptr, '\0', count * size);
	return (ptr);
}

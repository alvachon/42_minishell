/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <fboulang@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 13:50:52 by fboulang          #+#    #+#             */
/*   Updated: 2022/04/06 13:50:58 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>

static size_t	length(int n);

static size_t	length(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		len++;
	while (n)
	{
		n /= 10;
		len ++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*a;
	size_t	i;

	a = ft_calloc((length(n) + 1), sizeof (char));
	if (!a)
		return (NULL);
	i = length(n);
	if (n < 0)
	{
		a[0] = '-';
		n *= -1;
		if (n == -2147483648)
			n = 2147483647;
	}
	if (n == 0)
		a[0] = '0';
	while (n > 0)
	{
		a[i - 1] = n % 10 + 48;
		if (a[0] == '-' && n == 2147483647)
			a[i - 1] = '8';
		n /= 10;
		i--;
	}
	return (a);
}

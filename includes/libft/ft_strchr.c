/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <fboulang@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:21:44 by fboulang          #+#    #+#             */
/*   Updated: 2022/03/29 15:21:47 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	temp;

	i = 0;
	temp = (char) c;
	if (temp == '\0')
	{
		while (s[i] != '\0')
			i++;
		return ((char *) &s[i]);
	}
	else if (temp != '\0')
	{
		while (s[i] != '\0')
		{
			if (s[i] == temp)
				return ((char *) &s[i]);
			i++;
		}
	}
	return (NULL);
}

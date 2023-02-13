/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <fboulang@42quebec.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 09:46:05 by fboulang          #+#    #+#             */
/*   Updated: 2022/03/30 09:46:09 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	temp;

	i = 0;
	temp = (char) c;
	while (s[i] != '\0')
		i++;
	if (temp == '\0')
		return ((char *) &s[i]);
	else if (temp != '\0')
	{
		while (i > 0)
		{
			if (s[i] == temp)
				return ((char *) &s[i]);
			i--;
		}
		if (s[i] == temp)
			return ((char *) &s[i]);
	}
	return (NULL);
}

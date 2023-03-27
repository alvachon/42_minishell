/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   y_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fboulang <fboulang@42student.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 08:51:17 by fboulang          #+#    #+#             */
/*   Updated: 2023/03/15 08:51:18 by fboulang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/minishell.h"

int	y_echo(char *str)
{
	char	**buff;
	char	*temp;

	buff = ft_split(str, ' ');
	if (ft_strncmp(buff[1], "-n", 3) == 0)
	{
		temp = ft_substr(str, 9, ft_strlen(str));
		printf ("%s", temp);
	}
	else
	{
		temp = ft_substr(str, 6, ft_strlen(str));
		printf("%s\n", temp);
	}
	free (temp);
	free (buff);
	return (0);
}

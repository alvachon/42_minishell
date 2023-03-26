/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 14:23:42 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/26 13:54:46 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

int	z_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PWD=", 4) != 0)
		i++;
	printf("%s\n", ft_substr(env[i], 4, ft_strlen(env[i])));
	return (0);
}

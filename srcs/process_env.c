/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:35:32 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/05 19:48:33 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 DATA- Struct construction of shared information */
void	set_global(char **env)
{
	g_data.env = ft_setenv(env); /* malloqué un tableau ici pour mieux intéragir avec mes foncitons*/
	g_data.shell_state = SH_READ;
	g_data.pwd = ft_substr(set(1), 4, ft_strlen(set(1)));
	g_data.home = ft_substr(set(2), 5, ft_strlen(set(2)));
	printf("\n MINISHELL INFO SETTING (g_var):\n");
	printf("- pwd : %s\n", g_data.pwd);
	printf("- home : %s\n", g_data.home);
	printf("-----------\n");
}

char	*set(int code)
{
	int		i;

	i = 0;
	if (code == 1)
	{
		while (g_data.env[i] && ft_strncmp(g_data.env[i], "PWD=", 4) != 0)
			i++;
	}
	else if (code == 2)
	{
		while (g_data.env[i] && ft_strncmp(g_data.env[i], "HOME=", 5) != 0)
			i++;
	}
	return (g_data.env[i]);
}

void	sys_msg(char *reason, int code)
{
	if (code > 0)
	{
		perror(reason);
		exit(EXIT_FAILURE);
	}
}

char	**ft_setenv(char **env)
{
	int		i;
	int		j;
	char	**buff;

	i = 0;
	j = -1;
	while (env[i])
		i++;
	buff = ft_calloc(i + 1, sizeof(char *));
	while (++j < i)
		buff[j] = ft_strdup(env[j]);
	buff[j] = NULL;
	return (buff);
}

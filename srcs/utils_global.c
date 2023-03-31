/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_global.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:35:32 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/31 12:53:30 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 DATA- Struct construction of shared information */
void	set_global(char **env)
{
	g_data.env = ft_setenv(env); /* malloqué un tableau ici pour mieux intéragir avec mes foncitons*/
	g_data.shell_state = SH_READ;
	g_data.built_path = set("PATH=", 5);
	g_data.pwd = set("PWD=", 4);
	g_data.oldpwd = set("OLDPWD=", 7);
	printf("\n MINISHELL INFO SETTING (g_var):\n");
	printf("- path : %s\n", g_data.built_path);
	printf("- pwd : %s\n", g_data.pwd);
	printf("- oldpwd : %s\n", g_data.oldpwd);
	printf("-----------\n");
}

void	error_msg(char *cmd)
{
	char	**buff;

	buff = ft_split(cmd, ' ');
	write(2, "minishell: ", 12);
	write(2, buff[0], ft_strlen(buff[0]));
	write(2, " : Command not found.\n", 23);
	ft_freeall(buff);
	return ;
}

void	exit_msg(char *cmd)
{
	if (cmd)
	{
		write(1, "exit\n", 5);
		free(cmd);
	}
	clear_history();
	exit(EXIT_SUCCESS);
}

void	sys_msg(char *reason, int code)
{
	if (code == 2)
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

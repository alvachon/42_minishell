/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:25 by alvachon          #+#    #+#             */
/*   Updated: 2023/02/15 18:14:27 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* [0]BUILT [1]OPTION [2]REDIRECTION [3]APPEND [4]INFILE
* [5]PIPE [6]REDIRECTION [7]APPEND [8]OUTFILE */

#include "../includes/minishell.h"

char	**ft_pathfinder(char *envp[])
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	return (ft_split(envp[i], ':'));
}

int	builtincheck(char **cmd)
{
	int	i;

	i = 7;
	if (ft_strncmp(cmd[0], "echo", 5) == 0)
		i = 1;
	else if (ft_strncmp(cmd[0], "cd", 3) == 0)
		i = 2;
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		i = 3;
	else if (ft_strncmp(cmd[0], "export", 7) == 0)
		i = 4;
	else if (ft_strncmp(cmd[0], "unset", 6) == 0)
		i = 5;
	else if (ft_strncmp(cmd[0], "env", 4) == 0)
		i = 6;
	if (i <= 6)
		return (i);
	else
		return (envcheck(cmd));
}

int	functionparse_dispatch(char **env, char **cmd, int code)
{
	if (code == 1)
		echo_parse(cmd, env);
	/*if (code == 2)
		cd_parse_here(cmd, env);
	if (code == 3)
		pwd_parse_here(cmd, env);
	if (code == 4)
		export_parse_here(cmd, env);
	if (code == 5)
		unset_parse_here(cmd, env);
	if (code == 6)
		env_parse_here(cmd, env);
	if (code == 7)
		env_parse_here(cmd, env);*/
	return (0);
}

int	command_parse(char *cmd, char **env)
{
	char	**buff;
	char	**buff2;
	int		i;

	buff = ft_pathfinder(env);
	buff2 = ft_split(cmd, ' ');
	i = builtincheck(buff2);
	if (i == 8)
	{
		free (buff);
		free (buff2);
		return (1);
	}
	else
		return (functionparse_dispatch(buff, buff2, i));
}

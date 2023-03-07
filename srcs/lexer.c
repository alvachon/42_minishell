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
	{
		printf("Found echo\n");
		i = 1;
	}
	/*else if (ft_strncmp(cmd[0], "cd", 3) == 0)
	{
		printf("Found cd\n");
		i = 2;
	}*/
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
	{
		printf("Found pwd\n");
		i = 3;
	}
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
		parse_cd(cmd, env);*/
	if (code == 3)
		parse_pwd(cmd, env);
	/*if (code == 4)
		export_parse_here(cmd, env);
	if (code == 5)
		unset_parse_here(cmd, env);
	if (code == 6)
		env_parse_here(cmd, env);
	if (code == 7)
		env_parse_here(cmd, env);*/
	return (0);
}

int	command_parse(char *input, char **env)
{
	char	**paths;
	char	**cmds;
	int		i;

	if (ft_strcmp(input, "exit") == 0)
		exit_msg(input);
	paths = ft_pathfinder(env);
	cmds = ft_split(input, ' ');
	i = builtincheck(cmds);
	if (i == 8)
	{
		free (buff);
		free (buff2);
		return (1);
	}
	else
		return (functionparse_dispatch(buff, buff2, i));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:25 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/22 13:47:06 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* [0]BUILT [1]OPTION [2]REDIRECTION [3]APPEND [4]INFILE
* [5]PIPE [6]REDIRECTION [7]APPEND [8]OUTFILE */

#include "../includes/minishell.h"

int	builtincheck(t_cmd data)
{
	int	i;

	i = 7;

	if (ft_strncmp(data.built, "echo", 5) == 0)
		i = 1;
	/*else if (ft_strncmp(cmd[0], "cd", 3) == 0)
	{
		printf("Found cd\n");
		i = 2;
	}*/
	else if (ft_strncmp(data.built, "pwd", 4) == 0)
	{
		printf("Found pwd\n");
		i = 3;
	}
	else if (ft_strncmp(data.built, "export", 7) == 0)
		i = 4;
	else if (ft_strncmp(data.built, "unset", 6) == 0)
		i = 5;
	else if (ft_strncmp(data.built, "env", 4) == 0)
		i = 6;
	if (i <= 6)
		return (i);
	/*else
		return (envcheck(data.built));*/
	return (0);
}

int	functionparse_dispatch(char **env, char **cmds, int code)
{
	if (code == 1)
		echo_parse(cmds, env);
	/*if (code == 2)
		parse_cd(cmd, env);*/
	/*if (code == 3)
		parse_pwd(env);*/
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

char	**paths_search(void)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH=", g_data.env[i], 5) != 0)
		i++;
	return (ft_split(g_data.env[i], ':'));
}

/*
! Confirm with JU what to do with the exit function in the lexer ... [ ]
! Verify the error management if the implementation is still logic [ ]
! Verifiy if segemented data is parsed or not [ ]
 Lexer Step :
	1. Take the input as it is and put it in the struct
	2. Isolate the path from env with paht_search();
	3. Return a struct with segmented data (parser.c)
	4. Check if first called built in if from one of our asked implementation
		 If not, free and return 1 (I think its for error ...)
		 If yes, will parse the built in ...
*/

int	lexer(char *input)
{
	char	**paths;
	char	**cmds;
	t_cmd	data;
	int		i;

	if (ft_strcmp(input, "exit") == 0)
		exit_msg(input);
	cmds = NULL;
	data.input = input;
	paths = paths_search();
	data = parse(data);
	i = builtincheck(data);
	if (i == 1)
	{
		input = data.built;
		input = ft_strjoin(input, "|");
		if (data.opt)
		{
			data.opt = ft_strjoin(data.opt, "|");
			input = ft_strjoin(input, data.opt);
		}
		input = ft_strjoin(input, data.print);
		cmds = ft_split(input, '|');
	}
	if (i == 8)
	{
		free (paths);
		free (cmds);
		return (1);
	}
	else
		return (functionparse_dispatch(paths, cmds, i));
}

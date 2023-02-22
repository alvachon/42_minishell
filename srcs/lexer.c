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

char	**ft_pathfinder(char **env)
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH=", env[i], 5) != 0)
		i++;
	return (ft_split(env[i], ':'));
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

char *ltrim(char *input)
{
	while (*input <= 32)
		input++;
	return (input);
}

int	wordlen(char *input, int i)
{
	while (input[i] > 32)
		i++;
	return (i);
}

int scan(char *input, char c)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (input[i] == c)
			return (0);
		i++;
	}
	return (1);
	
}

int	guiltrim(char *input, char c)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(input);
	if (scan(input, c) == 1)
		return (len);
	while (input[i] != c)
	{
		i++;
		len--;
	}
	return (i);
}

char *wordtrim(char *input, int i)
{
	while (i >= 0)
	{
		input++;
		i--;
	}
	return (input);
}

char *keep_builtin(char *input, int i)
{
	input = ltrim(input);
	i = wordlen(input, i);
	g_data.input.built = ft_substr(input, 0, i);
	printf("%s\n", g_data.input.built);
	input = wordtrim(input, i);
	input = ltrim(input);
	return (input);
}

char *keep_option(char *input, int i)
{
	if (input[0] == '-' && input[1] == 'n' && input[2] <= 32)
	{
		g_data.input.opt = ft_substr(input, 0, 2);
		i = 2;
		input = wordtrim(input, i);
		input = ltrim(input);
	}
	return (input);
}


void	trim_guil(char *input, char c)
{
	char **cmd;
	char *file;
	int	word34;

	if (input[0] == c)
		input++;
	while (*input)
	{
		cmd = ft_split(input, c);
		file = cmd[0];
		if (g_data.input.print == NULL)
			g_data.input.print = file;
		else
			g_data.input.print = ft_strjoin(g_data.input.print, file);
		word34 = guiltrim(input, c);
		free (cmd);
		while (word34 >= 0)
		{
			input++;
			word34--;
		}
	}
}

char	*keep_print(char *input, int i)
{
	(void)i;
	if (input[0] != '<' || input[0] != '>' || input[0] != '|')
	{
		if (input[0] == 34)//"
		{
			trim_guil(input, 34);
			printf("input : %s\n", g_data.input.print);
		}
		else if (input[0] == 39)//'
		{
			trim_guil(input, 39);
			printf("input : %s\n", g_data.input.print);
		}
		else
		{
			trim_guil(input, 34);
			input = g_data.input.print;
			g_data.input.print = NULL;
			trim_guil(input, 39);
			printf("data keep : %s\n", g_data.input.print);
		}
	}
	printf("avant input : %s\n", input);
	while (*input)
	{
		if (*input == '<' || *input == '>' || *input == '|')
			break ;
		input++;
	}
	printf("apres input : %s\n", input);
	//trim aussi le input pour enlever ce qui a apres les flags
	//g_data.input.print = rtrim(g_data.input.print) implementer enlever espace de fin
	return (input);
}

char *keep_redir_input(char *input, int i)
{
	(void)i;//
	if (input[0] == '<' && input[1] <= 32)
	{
		g_data.input.redir_input = ft_substr(input, 0, 1);
		input++;
		input = ltrim(input);
	}
	return (input);
}

char *keep_flag_delim(char *input, int i)
{
	if (input[0] == '<' && input[1] == '<')
	{
		g_data.input.flag_delim = ft_substr(input, 0, 2);
		i = 2;
		input = wordtrim(input, i);
		input = ltrim(input);
	}
	return (input);
}

char *parse(char *input)
{
	int i;

	i = 0;
	while (*input)
	{
		input = keep_builtin(input, i);
		input = keep_option(input, i);
		input = keep_print(input, i);
		printf("parse : %s\n", input);
		input = keep_redir_input(input, i);
		input = keep_flag_delim(input, i);
		//input = keep_delimiter(input, i);
		printf("parse : %s\n", input);
		break ;
	}
	return (input);
}

int	command_parse(char *input)
{
	char	**paths;
	char	**cmds;
	int		i;

	if (ft_strcmp(input, "exit") == 0)//
		exit_msg(input);
	paths = ft_pathfinder(g_data.env);
	input = parse(input);
	exit(1);
	cmds = ft_split(input, ' ');
	i = builtincheck(cmds);
	if (i == 8)
	{
		free (paths);
		free (cmds);
		return (1);
	}
	else
		return (functionparse_dispatch(paths, cmds, i));
}

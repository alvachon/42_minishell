/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:55 by alvachon          #+#    #+#             */
/*   Updated: 2023/02/01 11:58:34 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//gcc minishell.c -lreadline
/*
 * [1]BUILT [2]OPTION [3]REDIRECTION [4]APPEND [5]INFILE [6]PIPE [7]REDIRECTION [8]APPEND [9]OUTFILE
 * */
#include "lib/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
    int i;
    i = 0;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) 
        i++;
    return (s1[i] - s2[i]);
}

char	**ft_pathfinder(char *envp[])
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH=", envp[i], 5) != 0)
		i++;
	return (ft_split(envp[i], ':'));
}

int	command_parse(char *cmd, char **env)
{
	/* Ce que l'on doit savoir sur une commande :
	1. est-ce qu'il y a une commande en tant que telle? Done
	1.a. Oui, on va vers 2.
	1.b. Non, on stop.
	2. Si cette commande existe, a-t-elle un flag? -> seulement echo peut utiliser un flag, et seulement -n.
	2.a. Oui, on va vers 3.
	2.b. Non, on va vers 4.
	3. Si cette commande a un flag, est-ce un flag qu'on gère?
	3.a. Oui, on va vers 4.
	3.b. Non, on stop.
	4. Qu'elle est de flag ou non, est-ce qu'elle a un argument?
	4.a. Oui, et elle prend un argument. On va vers 5.
	4.b. Non, elle ne prend pas un argument ou elle en prend un et il n'y en a pas. On stop.
	5. Est-ce que cet argument, s'il existe, est entre des guillemets?
	5.a. Oui, parse les guillemets. On va vers 6.
	5.b. On a terminé le parsing. On va vers 8.
	6. Single quotes ou double quotes?
	6.a. Single quotes : on ignore tout méta caractères.
	6.b. Double quotes : on prend en compte seulement $ comme méta caractère.
	7. Y'a-t-il un pipe ou une redirection?
	7.a. Oui, on redirige les outputs.
	7.b. Non, output non redirigé.*/

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

int	envcheck(char **cmd)
{
	if (ft_strncmp(cmd[0], "$", 1) == 0)
		return (7);
	else
		return (8);
}

void	error_msg(char *cmd)
{
	char	**buff;

	buff = ft_split(cmd, ' ');
	write (2, "minishell: ", 12);
	write (2, buff[0], ft_strlen(buff[0]));
	write (2, " : Command not found.\n", 23);
	return ;
}

char	**cmd_parse(char *cmd)
{
	// 1: look for "" or ''.
	// 2: if "", look for $ inside the "".
	// 3: else, seperate the string like so : [0]: echo [1]: flag [2]: arg.
	int		i;
	int		j;
	char	**buff;

	i = 0;
	j = 0;
	while (cmd[i] && cmd[i] != '"' && cmd[i] != 39)
		i++;
	if (!cmd[i])
		buff = ft_split(cmd, ' ');
	else
	{
		i = 0;
		while (cmd[i] != '"')
			i++;
		j = i + 1;
		while (cmd[j] != '"')
		{
			j++;
			if (cmd[j] == '"' && cmd[j + 1] != ' ')
				j++;
		}
		return (cmd_parse2(cmd, ft_substr(cmd, i + 1, j - 1)));
	}
	return (buff);
}

char	**cmd_parse2(char *cmd, char *arg)
{
	char	**buff;
	int		i;
	int		f;
	int		j;

	i = 0;
	f = 0;
	j = 0;
	while (cmd[i] && cmd[i] != '-')
		i++;
	if (!cmd[i])
		buff = ft_calloc(3, sizeof(char *));
	else
	{
		buff = ft_calloc(4, sizeof(char *));
		f++;
	}
	i = 0;
	while (cmd[i] != ' ')
		i++;
	buff[0] = ft_substr(cmd, 0, i);
	j = i;
	while (cmd[i] != ' ' && cmd[i] != '"' && cmd[i] != 39 && f == 1)
		i++;
	if (f == 1)
	{
		buff[1] = ft_substr(cmd, j, i);
		buff[2] = arg;
		buff[3] = NULL;
	}
	else
	{
		buff[1] = arg;
		buff[2] = NULL;
	}
	return (buff);
}

int	functionparse_dispatch(char **env, char **cmd, int code)
{
	if (code == 1)
		echo_parse(cmd, env);
	//if (code == 2)
		//echo_parse(cmd, env);
	/*if (code == 3)
		pwd_parse_here(cmd, env);
	if (code == 4)
		export_parse_here(cmd, env);
	if (code == 5)
		unset_parse_here(cmd, env);
	if (code == 6)
		env_parse_here(cmd, env);
	if (code == 7)
		envar_parse_here(cmd, env);*/
	return (0);
}

int main(int ac, char **av, char **env)
{
	int		infile;
	char	*cmd;

	(void)infile;
	(void)env;
	if (ac != 2)
	{
		//THIS IS 42ALMINISHELL BRANCH * * * * * * * * * * * * * * * * * * 
  		printf("Welcome! You can exit by pressing Ctrl+C at any time...\n");
		//signal redirection here
  		while (1)
		{
    		cmd = readline("minishell$ ");
    		if (!cmd)
      		{
				fprintf(stderr, "Usage: readline space allocation\n");
  				exit(EXIT_FAILURE);
			}
    		if (cmd[0] == '\0' || ft_strcmp(cmd, "\n") == 0)
            {
      	    	printf("Nothing, command freed, continue.\n");
      		    free(cmd);
      		    continue;
    		}
    		if (ft_strcmp(cmd, "exit") == 0)
            {
     		    printf("exit, command freed, goodbye.\n");
				clear_history();
      		    free(cmd);
      		    exit(EXIT_SUCCESS);
    		}
    		//printf("%s\n", cmd);
			add_history(cmd);
			if (command_parse(cmd, env) == 1)
				error_msg(cmd);
			else
				printf("Command done and freed, added to the history\n");
			// readline malloc's a new buffer every time
    		free(cmd);
  		}
	}
	fprintf(stderr, "Usage: %s <file>\n", av[0]);
  	exit(EXIT_FAILURE);
}

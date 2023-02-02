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

int	**command_parse(char *cmd, char **env)
{
	char	**buff;
	char	**buff2;

	buff = ft_pathfinder(env);
	buff2 = ft_split(cmd, ' ');
	if (builtincheck(buff2) == 1)
		return (1);
	else
		return (0);
}

int	builtincheck(char **cmd)
{
	int	i;

	if (ft_strncmp(cmd[0], "echo", 5) != 0)
		i++;
	if (ft_strncmp(cmd[0], "cd", 3) != 0)
		i++;
	if (ft_strncmp(cmd[0], "pwd", 4) != 0)
		i++;
	if (ft_strncmp(cmd[0], "export", 7) != 0)
		i++;
	if (ft_strncmp(cmd[0], "unset", 6) != 0)
		i++;
	if (ft_strncmp(cmd[0], "env", 4) != 0)
		i++;
	if (i < 6)
		return (0);
	else
		return (1);
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
    		printf("%s\n", cmd);
			add_history(cmd);
			printf("Command done and freed, added to the history\n");
			// readline malloc's a new buffer every time
    		free(cmd);
  		}
	}
	fprintf(stderr, "Usage: %s <file>\n", av[0]);
  	exit(EXIT_FAILURE);
}

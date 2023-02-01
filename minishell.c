/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:55 by alvachon          #+#    #+#             */
/*   Updated: 2023/01/31 14:52:31 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//gcc minishell.c -lreadline
/*
 * [1]BUILT [2]OPTION [3]REDIRECTION [4]APPEND [5]INFILE [6]PIPE [7]REDIRECTION [8]APPEND [9]OUTFILE
 * */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>
#include<errno.h>

int	ft_strcmp(char *s1, char *s2)
{
    int i;
    i = 0;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) 
        i++;
    return (s1[i] - s2[i]);
}

int main(int ac, char **av, char **env)
{
	int		infile;
	char	*cmd;

	if (ac != 2)
	{
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
				rl_clear_history
      		    free(cmd);
      		    exit(EXIT_SUCCESS);
    		}
			//lexical_parsing_here(cmd);
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

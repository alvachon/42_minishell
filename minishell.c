/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:55 by alvachon          #+#    #+#             */
/*   Updated: 2023/02/06 12:57:34 by alvachon         ###   ########.fr       */
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
#include<termios.h>

typedef struct s_process
{
	struct s_process	*next;//Next process in pipeline
	char				*argv;//For exect
	pid_t				pid;//Process ID
	char				completed;//True if process has completed
	char				stopped;//True if process has stopped
	int					status;//report status value
}	t_process
;

typedef struct s_job
{
	struct s_job	*next;//Next active job
	char			*command;//Command line, used for messages
	t_process		*first_process;//list of processes in this job
	pid_t			pgid;//process group ID
	char			notified;//true if user told about stopped job
	struct termios	tmodes;//saved terminal modes
	int				stdin;//standard entry (0) i/o channel
	int				stdout;//standard exit (1) i/o channel
	int				stderr;//standard error exit (2) i/o channel
}	t_job
;

int	ft_strcmp(char *s1, char *s2)
{
    int i;
    i = 0;
    while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) 
        i++;
    return (s1[i] - s2[i]);
}

void	init_shell()
{
	int				shell_terminal;
	int				shell_is_interactive;
	struct termios	term1;


	shell_terminal = STDIN_FILENO;
	shell_is_interactive = isatty(shell_terminal);
	if (shell_is_interactive)
	{
		if (tcgetattr(STDIN_FILENO, &term1) != 0)
    		perror("tcgetattr() error");
		else
		{
			printf("the original end-of-file character is x'%02x'\n", term1.c_cc[VEOF]);
			term1.c_cc[VEOF] = 'z';
 			if (tcsetattr(STDIN_FILENO, TCSANOW, &term1) != 0)
      			perror("tcsetattr() error");
    		if (tcgetattr(STDIN_FILENO, &term1) != 0)
      			perror("tcgetattr() error");
   			else
      			printf("the new end-of-file character is x'%02x'\n", term1.c_cc[VEOF]);
		}
	}
}

int main(int ac, char **av, char **env)
{
	//pid_t			shell_pgid;
	char	*cmd;

	if (ac != 2)
	{
		//THIS IS 42ALMINISHELL BRANCH * * * * * * * * * * * * * * * * * * 
  		printf("Welcome! You can exit by pressing Ctrl+C at any time...\n");
		//Break Terminal Signals here
		init_shell();
  		while (1)//This part is named Foreground Job (gets input)
		{
			/*signal_handler(process_a);*/
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
      		    free(cmd);
      		    exit(EXIT_SUCCESS);
    		}
			/*lexical_parsing_here(cmd);*/
			//This part is Background job
			/*signal_handler(process_b);*/
			/*if (simple_command)
				Do(command_builtins);*/
			/*else
			 {
				fork_process();
				-> in child (exect requested command and never return);
				->* in parent (wait for child to complete); */
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

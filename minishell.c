/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:55 by alvachon          #+#    #+#             */
/*   Updated: 2023/02/06 15:21:36 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//gcc minishell.c -lreadline
/*
 * [1]BUILT [2]OPTION [3]REDIRECTION [4]APPEND [5]INFILE [6]PIPE [7]REDIRECTION [8]APPEND [9]OUTFILE
 * */
#include "lib/minishell.h"

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
		envar_parse_here(cmd, env);*/
	return (0);
}

void	echo_parse(char **cmd, char **env)
{
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	temp = ft_strjoin("/", cmd[0]);
	while (env[i])
	{
		temp2 = ft_strjoin(env[i], temp);
		if (access(temp2, F_OK) == 0)
		{
			execute_echo(temp2, cmd, env);
			free_echo(temp, temp2, env, 3);
			return ;
		}
		else
		{
			i++;
			free_echo (temp, temp2, env, 1);
		}
	}
	free_echo (temp, temp2, env, 2);
}

void	free_echo(char *temp, char *temp2, char **env, int code)
{
	int	i;

	i = 0;
	(void)env;
	if (code == 1)
		free(temp2);
	if (code == 2)
	{
		while (env[i])
		{
			free (env[i]);
			i++;
		}
		free (env);
		free (temp2);
		if (*temp)
			free (temp);
	}
	if (code == 3)
		free(temp);
}

void	execute_echo(char *path, char **cmd, char **env)
{
	pid_t	exe;
	int		i;
	int		j;

	i = -1;
	j = -1;
	exe = fork();
	if (exe == 0)
		execve(path, cmd, env);
	else
		wait(0);
	while (cmd[i++])
		free(cmd[i]);
	while (env[j++])
		free(env[j]);
	free (cmd);
	free (env);
	free (path);
	return ;
}


/*Changes the attributes associated with a terminal. 
New attributes are specified with a termios control structure.
Programs should always issue a tcgetattr() first, modify the desired fields, and then issue a tcsetattr().
tcsetattr() should never be issued using a termios structure that was not obtained using tcgetattr().
tcsetattr() should use only a termios structure that was obtained by tcgetattr().*/


void	init_shell()
{
	int				std_terminal_input;
	int				is_std_terminal;
	struct termios	saved_attributes;
	struct termios	custom_attributes;

	std_terminal_input = STDIN_FILENO;
	is_std_terminal = isatty(std_terminal_input);
	if (is_std_terminal)
	{
		if (tcgetattr(STDIN_FILENO, &saved_attributes) != 0)
		{
    		perror("tcgetattr() error : Failed to save standard terminal attributes\n");
			exit (EXIT_FAILURE);
		}
		else
		{
			/*atexit(reset_input_mode)*/
			//term.c_cc[VINTR] //CTRL-C -> CTRL-D
			//term.c_cc[VEOF]// CTRL-D -> CTRL-C ?
			//term.c_cc[VEOL]// CTRL-D -> CTRL-C ?
			tcgetattr(STDIN_FILENO, &custom_attributes);
			printf("Original EOF Character is :'%02x'\n", saved_attributes.c_cc[VEOF]);
			printf("Original CTRL-C Character is :'%02x'\n", saved_attributes.c_cc[VINTR]);
			custom_attributes.c_cc[VEOF] = VINTR;
 			if (tcsetattr(STDIN_FILENO, TCSANOW, &custom_attributes) != 0)//make the change immediatly
      			perror("tcsetattr() error");
    		if (tcgetattr(STDIN_FILENO, &custom_attributes) != 0)
      			perror("tcgetattr() error");
   			else
      			printf("New EOF Character is :'%02x'\n", custom_attributes.c_cc[VEOF]);
	      	printf("Ne fonctionne pas pour l'instant\n");
		}
	}
	else
	{
    	perror("Not a terminal.\n");
		exit (EXIT_FAILURE);
	}
}

int main(int ac, char **av, char **env)
{
	//pid_t			shell_pgid;
	int		infile;
	char	*cmd;

	(void)infile;
	(void)env;
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
    			perror("Usage: readline space allocation\n");
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
				/*reset_terminal_input_mode();*/ //Pas acces a atexit(); ft
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
			if (command_parse(cmd, env) == 1)
				error_msg(cmd);
			else
				printf("Command done and freed, added to the history\n");
			// readline malloc's a new buffer every time
    		free(cmd);
  		}
	}
	fprintf(stderr, "Usage: %s <file>\n", av[0]);//need to be change later
  	exit(EXIT_FAILURE);
}

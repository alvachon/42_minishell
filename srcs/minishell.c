/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 13:27:55 by alvachon          #+#    #+#             */
/*   Updated: 2023/02/09 15:07:51 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* [1]BUILT [2]OPTION [3]REDIRECTION [4]APPEND [5]INFILE
* [6]PIPE [7]REDIRECTION [8]APPEND [9]OUTFILE */

#include "../includes/minishell.h"

volatile sig_atomic_t gotint = 0;
extern void quitHandler(int);

#define FOREGROUND_JOB 1

typedef struct s_terminal
{
	struct termios		mod_terminal;
	struct termios		new_options;
	struct sigaction	quit_action;
	int					tty_stdin;
	int					tty_stdout;
	//char			**env;
	//char			*user;
}	t_terminal
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
		return (0/*functionparse_dispatch(buff, buff2, i)*/);
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
		env_parse_here(cmd, env);*/
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
void	handle_sigint(int signum)
{
	/* Signal safety: It is not safe to call clock(), printf(),
     * or exit() inside a signal handler. Instead, we set a flag.*/
	(void)signum;
	signal(SIGINT, SIG_IGN);
	gotint = 1;
	
}

void	quit_shell(t_terminal *minishell)
{
	printf("CTRL-D. Don't forget to clean struct\n");
	printf("exit, goodbye.\n");
	gotint = 0;
	//tcsetattr(STDIN_FILENO, TCSANOW, &(*minishell).mod_terminal);
    exit(EXIT_SUCCESS);
}

void	init_shell(t_terminal *minishell)
{
	if (isatty(STDIN_FILENO))
	{
		tcgetattr(STDIN_FILENO, &(*minishell).mod_terminal);
		(*minishell).tty_stdin = dup(STDIN_FILENO);
		(*minishell).tty_stdout = dup(STDOUT_FILENO);
		(*minishell).new_options = (*minishell).mod_terminal;
		(*minishell).new_options.c_cc[VEOF] = 3;
		(*minishell).new_options.c_cc[VINTR] = 4;
		tcsetattr(STDIN_FILENO,TCSANOW,&(*minishell).new_options);
		signal(SIGINT, handle_sigint);
	}
	else
	{
    	perror("init_shell : Not a terminal.\n");
		exit (EXIT_FAILURE);
	}
}

int main(int ac, char **av, char **env)
{
	t_terminal		minishell;
	char			*cmd;
	//THIS IS 42ALMINISHELL BRANCH * * * * * * * * * * * * * * * * * * 
	if (ac != 2)
	{
		init_shell(&minishell);
  		while (FOREGROUND_JOB)
		{
			if (ttyname(0))
			{
				/*lexical_parsing_here(cmd);*/
				if (gotint == 1)
					quit_shell(&minishell);
    			cmd = readline("minishell$ ");
    			if (!cmd)
					continue;
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
					gotint = 0;
					tcsetattr(STDIN_FILENO, TCSANOW, &(minishell).mod_terminal);
      		    	free(cmd);
      		    	exit(EXIT_SUCCESS);
    			}
				/*if (simple_command)
					Do(command_builtins);
				  else
					fork_process();*/
			}
			else //enter pipe process
				printf("\n(job process) Is redirected, not a terminal. \n");
    		printf("%s\n", cmd);
			add_history(cmd);
			if (command_parse(cmd, env) == 1)
				error_msg(cmd);
			else
				printf("Command done and freed, added to the history\n");
    		free(cmd);
  		}
	}
	fprintf(stderr, "Usage: %s <file>\n", av[0]);//need to be change later
  	exit(EXIT_FAILURE);
}

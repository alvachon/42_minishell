/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:06:16 by fboulang          #+#    #+#             */
/*   Updated: 2023/02/08 15:53:27 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "libft/libft.h"
# include "readline.h"
# include "history.h"
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>
# include <locale.h>
# include <signal.h>
# include <fcntl.h>
# include <termios.h>


typedef struct s_argsandflags
{
	char	*buff;
	char	**arg;
	char	*path;
}			t_aflg;

char	**ft_pathfinder(char *envp[]);
//int		command_parse(char *cmd, char **env);
int		builtincheck(char **cmd);
int		envcheck(char **cmd);
//int		functionparse_dispatch(char **env, char **cmd, int code);
void	error_msg(char *cmd);
void	echo_parse(char **cmd, char **env);
void	execute_echo(char *path, char **cmd, char **env);
void	free_echo(char *temp, char *temp2, char **env, int code);

/* ALEX PART - - - */


typedef struct s_process
{
	struct s_process	*next;//Next process in pipeline
	char				*argv;//For exect
	pid_t				pid;//Process ID
	char				completed;//True if process Hhas completed
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
}	t_job
;

#endif
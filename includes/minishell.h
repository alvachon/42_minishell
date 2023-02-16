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

#define FOREGROUND_JOB 1

typedef struct s_argsandflags
{
	char	*buff;
	char	**arg;
	char	*path;
}			t_aflg;

typedef struct s_terminal
{
	struct termios		mod_terminal;
	struct termios		new_options;
}	t_terminal;

int		envcheck(char **cmd);
int		ft_getchar(void);

/*init.c*/
void	handle_sig(int sign);
void	init_shell(t_terminal *minishell);
/*lexer.c*/
char	**ft_pathfinder(char *envp[]);
int		builtincheck(char **cmd);
int		functionparse_dispatch(char **env, char **cmd, int code);
int		command_parse(char *cmd, char **env);
/*message.c*/
void	error_msg(char *cmd);
void    exit_msg(char *cmd, t_terminal *minishell);
void    sys_msg(char *reason, int code);
/*z_echo.c*/
void	free_echo(char *temp, char *temp2, char **env, int code);
void	execute_echo(char *path, char **cmd, char **env);
void	echo_parse(char **cmd, char **env);

#endif
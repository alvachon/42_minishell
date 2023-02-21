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

enum	e_shell_state
{
	SH_READ,
	SH_EXEC,
}
;
typedef struct s_data
{
	char				**env;
    char                *built_path;
    char                *pwd;
    char                *oldpwd;
	enum e_shell_state	shell_state;
}	t_data
;

t_data	g_data;

int		envcheck(char **cmd);
int		ft_getchar(void);

/*init.c*/
void	handle_sig(int sign);
char    *set_built_path();
char    *set_pwd();
char    *set_old_pwd();
void	set_global(char **env);
void	init_shell(t_terminal *minishell, char **env);
/*lexer.c*/
int		builtincheck(char **cmd);
char	**ft_pathfinder(char *envp[]);
int		functionparse_dispatch(char **env, char **cmd, int code);
int		command_parse(char *cmd, char **env);
/*message.c*/
void	error_msg(char *cmd);
void    exit_msg(char *cmd);
void    sys_msg(char *reason, int code);

void    free_exect(char **cmd, char **env, char *path);

/*z_echo.c*/
void	free_echo(char *temp, char *temp2, char **env, int code);
void	execute_echo(char *path, char **cmd, char **env);
void	echo_parse(char **cmd, char **env);

/*z_pwd.c*/
void	free_pwd(char *temp, char *temp2, char **env, int code);
void	execute_pwd(char *path, char **cmd, char **env);
void	parse_pwd(char **cmd, char **env);

#endif

/*

int	ft_slen(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int ft_isspace(char c)
{
    if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
        return (1);
    else
        return (0);
}

char *ft_rtrim(char *s)
{
    char *back = s + ft_slen(s);
    while(isspace(*--back))
        *(back + 1) = '\0';
    return (s);
}

int	ft_getchar()
{
	char buf[BUFSIZ];
	char *bufptr;
	int i;

	bufptr = buf;
	i = 0;
	if (i == 0)
	{
		i = read(0, buf, 1);
		bufptr = buf;
	}
	if (--i >= 0)
		return (*bufptr++);
	return (0);
}

void *ft_realloc(void *ptr, size_t size)
{
    void *new;

    if (!ptr)
	{
        new = malloc(size);
        if (!new)
			return (NULL);
    }
	else
	{
        if (sizeof(ptr) < size)
		{
            new = malloc(size);
            if (!new)
				return (NULL);
            ft_memcpy(new, ptr, sizeof(ptr));
            free(ptr);
        }
		else
            new = ptr;
    }
	return (new);
}

char *ft_readline()
{
    int 	buf_siz;
	int 	str_siz;
	char	*buf;
    int     ix;
    int     ch;
	
    ix = 0;
	buf_siz = 64;
    buf = malloc(buf_siz);
    str_siz = buf_siz;
    while (1)
	{
        if (ix == str_siz - 1)
        {
            if (!buf_siz)
                break ;
            buf_siz += buf_siz;
            buf = ft_realloc(buf, buf_siz);
            str_siz = buf_siz;
        }
        ch = ft_getchar();
        if (ch == EOF)
        {
            if (buf_siz)
                free(buf);
            return (NULL);
        }
        if (ch == '\n')
            break;
        buf[ix] = ch;
        ix++;
    }
    buf[ix] = '\0';
    return (buf);
}*/
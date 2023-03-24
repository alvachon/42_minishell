/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:06:16 by fboulang          #+#    #+#             */
/*   Updated: 2023/03/24 16:21:56 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "history.h"
# include "libft/libft.h"
# include "readline.h"
# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <locale.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define FOREGROUND_JOB 1

typedef struct s_argsandflags
{
	char				*buff;
	char				**arg;
	char				*path;
}						t_aflg;

typedef struct s_terminal
{
	struct termios		mod_terminal;
	struct termios		new_options;
}						t_terminal;

enum					e_shell_state
{
	SH_READ,
	SH_EXEC,
};

typedef struct s_cmd
{
	char				*input;
	char				*built;
	char				*opt;
	char				*print;
	char				*redir_input;
	char				*flag_delim;
}						t_cmd;
typedef struct s_data
{
	char				**env;
	char				*built_path;
	char				*pwd;
	char				*oldpwd;
	char				*home;
	enum e_shell_state	shell_state;
}						t_data;

t_data					g_data;

char					*scan_end(char *file, int trig);

/*input_lexer.c*/
void					keep_builtin(int i, t_cmd *data);
void					keep_option(int i, t_cmd *data);
void					keep_print(int i, t_cmd *data);
t_cmd					parse(t_cmd data);

/*input_merge.c*/
int						envcheck(char **cmd);
int						builtincheck(t_cmd data);
int						functionparse_dispatch(char **env, char **cmds,
							int code);
int						lexer(char *input);

/*terminal_signal.c*/
void					ctrl_c_eof(void);
void					handle_sig(int sign);
void					init_shell(t_terminal *minishell, char **env);

/*terminal_struct.c*/
void					set_global(char **env);
void					error_msg(char *cmd);
void					exit_msg(char *cmd);
void					sys_msg(char *reason, int code);

/*utils_clear.c*/
int						wordlen(char *input, int i);
char					*wordtrim(char *input, int i);
int 					scan(char *input, char c);
int						chartrim(char *input, char c);
int						wordcount(char *str);

/*utils_env.c*/
char					*path(char *home);
char					*set(char *var, int siz_var);
char					**paths_search(void);

/*utils_trim.c*/
char					*ulstr(char *str);
char					*ltrim(char *input);
char					*rtrim(char *str);
char					*trimchar(char *file, char c);
void					trim_guil(t_cmd **data, char c, int trig);

/*z_cd.c*/
int						z_cd(char *str, char **env);

/*z_echo.c*/
void					free_echo(char *temp, char *temp2, char **env,
							int code);
void					execute_echo(char *path, char **cmd, char **env);
void					echo_parse(char **cmd, char **env);

/*z_env.c*/
int						z_env(char **env);

/*z_export.c*/
int						z_export(char *str, char **env);
char					**export_env(char *str, char **env);
char					*new_env_var(char *str, char *var);

/*z_pwd.c*/
int						z_pwd(/*char **env*/void);

/*z_unset.c*/
int						z_unset(char *str, char **env);
char					**env_unset(char *str, char **env);

int						move_info(char *str);

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

int	ft_isspace(char c)
{
    if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
		|| c == ' ')
        return (1);
    else
        return (0);
}

char	*ft_rtrim(char *s)
{
	char	*back;

    back = s + ft_slen(s);
    while(isspace(*--back))
        *(back + 1) = '\0';
    return (s);
}

int	ft_getchar(void)
{
	char	buf[BUFSIZ];
	char	*bufptr;
	int		i;

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

void	*ft_realloc(void *ptr, size_t size)
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

char	*ft_readline(void)
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
            break ;
        buf[ix] = ch;
        ix++;
    }
    buf[ix] = '\0';
    return (buf);
}*/

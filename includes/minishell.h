/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:06:16 by fboulang          #+#    #+#             */
/*   Updated: 2023/04/04 12:26:38 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "history.h"
# include "libft/libft.h"
# include "readline.h"
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
	char				*path;
	char				*rawinput;
}						t_cmd;
typedef struct s_data
{
	char				**env;
	char				*built_path;
	char				*pwd;
	char				*home;
	enum e_shell_state	shell_state;
}						t_data;

t_data					g_data;

/*lexer.c*/
int 					ft_error(int code);
int						builtincheck(t_cmd data, char **env);
int						lexer(char *input, char **env);

/*minishell.c*/
int						shell_process(char **env);

/*parse.c*/
void					keep_print(int i, t_cmd *data);
void					keep_option(t_cmd *data);
void					keep_builtin(int i, t_cmd *data);
char					*ft_strpaste(char *already_here, char *new);
t_cmd					parse(t_cmd data);

/*terminal_signal.c*/
void					handle_sig(int sign);
void					ctrl_c_eof(void);
void					init_shell(t_terminal *minishell, char **env);

/*utils_env.c*/
char					*set(int code);
void					option(t_cmd *data, char *option, int trigger, int trim_size);
void					hard_path(t_cmd *data);
void					remake_path(t_cmd *data);

/*utils_global.c*/
void					set_global(char **env);
void					error_msg(char *cmd);
void					exit_msg(char *cmd);
void					sys_msg(char *reason, int code);
char					**ft_setenv(char **env);

/*utils_input.c*/
int						wordlen(char *input, int i);
char					*wordtrim(char *input, int i);
int						wordcount(char *str);
int						scan(char *input, char c);
int						chartrim(char *input, char c);

/*utils_trim.c*/
void					trim_guil(t_cmd **data, char c, int trig);
char					*ulstr(char *str);
char					*ltrim(char *input);
char					*rtrim(char *str);
char					*trimchar(char *file, char c);

/*work_in_progress.c*/
void					keep_redir_input(t_cmd data, int i);
char					*scan_end(char *file, int trig);
void					keep_flag_delim(t_cmd data, int i);

/*z_cd*/
int						delete_last(t_cmd data);
char					*rewrite(t_cmd *data, int i);
void					keep_user(t_cmd *data);
int						z_cd(t_cmd data, char **env);

/*z_echo.c*/
int						z_echo(t_cmd data, char **env);

/*z_env.c*/
int						z_env(char **env);

/*z_export*/
int						z_export(char *str);
char					**export_env(char *str);
char					*new_env_var(char *str, int pos);
int						ft_exportcomp(const char *str, char *var);

/*z_pwd.c*/
int						z_pwd(char **env);

/*z_unset.c*/
int						z_unset(char *str);
char					**env_unset(char *str);
int						ft_unsetcomp(const char *str, char *var);

/*z_exit.c*/
int						z_exit(t_cmd data, int status);
void					data_free(t_cmd *data);

#endif

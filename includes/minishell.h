/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:06:16 by fboulang          #+#    #+#             */
/*   Updated: 2023/04/06 11:45:08 by alvachon         ###   ########.fr       */
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
}						t_cmd;

typedef struct s_data
{
	char				**env;
	char				*pwd;
	char				*home;
	enum e_shell_state	shell_state;
}						t_data;

t_data					g_data;

/*lexer.c*/
/*piper here ?*/
t_cmd					parse(t_cmd data);
int 					ft_error(int code);
void					data_free(t_cmd *data);
int						builtincheck(t_cmd data, char **env);
int						lexer(char *input, char **env);

/*parse.c*/
void					keep_redir_input(int i, t_cmd *data);
/*void					keep_flag_delim(t_cmd data, int i);*/
void					keep_print(int i, t_cmd *data);//
void					keep_option(t_cmd *data);
void					keep_builtin(int i, t_cmd *data);

/*process_shell.c*/
void					handle_sig(int sign);
void					ctrl_c_eof(void);
void					init_shell(t_terminal *minishell, char **env);
int						shell_process(char **env);

/*process_env.c*/
void					set_global(char **env);
char					*set(int code);
void					sys_msg(char *reason, int code);
char					**ft_setenv(char **env);

/*utils_built*/
int						wordlen(char *input, int i);
char					*ltrim(char *input);
char					*wordtrim(char *input, int i);
char					*ulstr(char *str);
char					*trimchar(char *file, char c);

/*utils_print.c*/
int						scan(char *input, char c);
int						chartrim(char *input, char c);
char 					*repurpose(char *str, int code);
char					*print_var(char *var);
int						token_reach(int i, char *str);

/*z_cd*/
char					*ft_strpaste(char *already_here, char *new);
void					remove_section(t_cmd *data);
void					add_section(t_cmd *data);
void					do_relative_path(t_cmd *data);
void					do_direct_path(t_cmd *data);
int						z_cd(t_cmd data);

/*z_echo.c*/
char					*add_content(char *content, char *add, int position);
void					do_guil(t_cmd *data, int i);
void					do_sp(t_cmd *data, int i);
void					do_ref(t_cmd *data, int i);
int						z_echo(t_cmd data, char **env);

/*z_print.c*/
int						z_env(char **env);
int						z_pwd(char **env);
int						z_exit(t_cmd data, int status);

/*z_export*/
int						z_export(char *str);
char					**export_env(char *str);
char					*new_env_var(char *str, int pos);
int						ft_exportcomp(const char *str, char *var);

/*z_unset.c*/
int						z_unset(char *str);
char					**env_unset(char *str);
int						ft_unsetcomp(const char *str, char *var);

#endif

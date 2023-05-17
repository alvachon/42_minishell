/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:06:16 by fboulang          #+#    #+#             */
/*   Updated: 2023/05/16 10:55:31 by alvachon         ###   ########.fr       */
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
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

enum					e_shell_state
{
	SH_READ,
	SH_EXEC,
	SH_CHILD,
};

typedef struct s_terminal
{
	int					shell_terminal;
	int					shell_is_interactive;
	char				*prompt;
	char				*cmd;
	struct termios		mod_terminal;
	struct termios		new_options;
}						t_terminal;

typedef struct s_index
{
	int	i;
	int	j;
	int	k;
}		t_in;

typedef struct s_cmd
{
	char				*built;
	char				*opt;
	int					in;
	int					out;
	char				*print;
	char				*path;
	char				*temp;
	char				*flag_delim;
	int					iter;
}						t_cmd;

typedef struct s_node
{
	int					index;
	int					fds[2];
	char				*input;
	int					err;
	t_cmd				job;
	struct s_node		*next;
	struct s_node		*prev;
}						t_node;

typedef struct s_data
{
	char				**env;
	char				*pwd;
	char				*home;
	int					retval;
	int					pipenum;
	pid_t				children;
	enum e_shell_state	shell_state;
}						t_data;

t_data					g_data;

/*minishell.c *///------3
int			job_process(t_node *process);
t_node		*shell_process(t_node *process, t_terminal *mini);
int			main(int ac, char **av, char **env);

/*0_env.c*///-----------5
char		*set(int code);
char		**ft_setenv(char **env);
t_in		init_ind(void);
int			ft_errormsg(int code);
int			ft_error(int code);

/*0_signal.c*///-----------5
void		handle_sig(int sign);
void		input_eof(void);
void		display_cmd(t_terminal *mini);
void		set_global(char **env);
void		init_shell(t_terminal *minishell, char **env);

/*1_parse.c*///-----------5
void		keep_token(int i, t_node *node);
void		keep_print(int i, t_node *node);
void		keep_option(t_node *node);
void		keep_builtin(int i, t_node *node);
void		parse(t_node *node);

/*2_expand.c*///-----------5
char		*print_var(char *str);
char		*repurpose(char *str, int code);
char		*rm_ref(char *input, int i, int l);
char		*find_expand(int i, char *input);
char		*check_expand(int i, char *input);

/*3_process.c*///-----------4
void		data_free(t_node *node);
void		set_memjob(t_node *node);
t_node		*init_node(t_node *node);
t_node		*queue_jobs(t_node *node, char *input);

/*4_execution.c*///-----------5
int			exect_cmd(t_node *node);
int			ft_dispatch_exec(t_node *node);
int			exec_rel(t_node *node, char	*path);
int			exec_bin(t_node *node);
void		exec_child(t_node *node, char *path);

/*4_utils_execution.c*///-----------5
char		*cmd_exists(char **paths, t_cmd *data);
char		**paste_and_sep(t_cmd *data);
int			ft_pathfinder(void);
int			get_rel(t_cmd *data, t_node *node);
int			builtin_check(t_node *node);

/*4_utils_path.c*///-----------5
int			set_file(int file, char *temp, t_node *node);
char		*ft_strpaste(char *ah, char *new);
void		do_relative_path(t_node *node);
void		do_direct_path(t_node *node);
void		do_home_path(t_node *node);

/*4_utils_redir.c*///-----------5
int			do_input(int i, t_node *node);
char		*do_cmd(char *cmd);
int			sub_readline(char *cmd, char *delim);
int			do_heredoc(int i, t_node *node);
int			do_output(int i, t_node *node, int code);

/*5_pipes.c*///-----------3
int			child_pipe_in(t_node *node, int code);
int			pipe_out(t_node *node, int code);
int			pipers(t_node *process);

/*lib_built.c*///-----------5
int			wordlen(char *input, int i);
char		*ltrim(char *input);
char		*wordtrim(char *input, int i);
char		*ulstr(char *str);
char		*trimchar(char *file, char c);

/*lib_print.c*///-----------5
int			scan(char *input, char c);
int			skip_simple_guil(int i, char *input);
int			chartrim(char *input, char c);
int			token_limit(char c);
int			token_reach(int i, char *str);

/*lib_read.c*///-----------5
int			ft_getchar(int fd);
int			ft_isspace(char *cmd);
void		*ft_realloc(void *ptr, size_t size);
int			ft_stristr(const char *haystack, const char *needle, size_t len);
void		free_buff(char **buff, int i);

/*lib_readline.c*///-----------5
int			isallnum(char *str);
int			check_buffer(int buf_siz, char **buf, int str_siz);
int			check_end(int fd, int buf_siz, char **buf);
char		*check_delim(int trigger, int i, char *buf, char *delim);
char		*ft_readline(int fd, int trigger, char *delim);

/*z_cd*///-----------5
void		trim_spec(int code, t_node *node);
char		*subtrim(int i, t_node *node);
void		remove_section(t_node *node);
void		add_section(t_node *node);
int			z_cd(t_cmd data);

/*z_echo.c*///--------5
int			scan_for_word(char *input);
char		*add_content(char *content, char *add, int position, char *var);
void		do_guil(t_node *node, int i);
void		do_sp(t_node *node, int i);
int			z_echo(t_cmd data, char **env);

/*z_export*///-----5
int			z_export(char *str);
char		**export_env(char *str);
char		*new_env_var(char *str, int pos);
int			ft_exportcomp(const char *str, char *var);
int			identchecker(char *str);

/*z_print.c*///---------3
int			z_env(void);
int			z_pwd(t_node *node);
int			z_exit(t_node *node, char *status);

/*z_unset.c*///--------5
int			z_unset(char *str);
char		**env_unset(char *str);
int			ft_unsetcomp(const char *str, char *var);
void		free_the_vars(char **vars);
void		free_the_env(void);

#endif

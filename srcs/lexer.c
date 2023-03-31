/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:25 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/26 19:19:45 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* [0]BUILT [1]OPTION [2]REDIRECTION [3]APPEND [4]INFILE
 [5]PIPE [6]REDIRECTION [7]APPEND [8]OUTFILE */

#include "../includes/minishell.h"

int ft_error(int code)
{
	if (code > 0)
		perror("Error:");
	return (code);
}

int	builtincheck(t_cmd data, char **env)
{
	int	r;
	
	r = 0;
	if (ft_strncmp(data.built, "echo", 5) == 0)
		r = z_echo(data, g_data.env);
	else if (ft_strncmp(data.built, "cd", 3) == 0)
		r = z_cd(data, g_data.env);
	else if (ft_strncmp(data.built, "pwd", 4) == 0)
		r = z_pwd(env);
	else if (ft_strncmp(data.built, "export", 7) == 0)
		r = z_export(data.print);
	else if (ft_strncmp(data.built, "unset", 6) == 0)
		r = z_unset(data.print);
	else if (ft_strncmp(data.built, "env", 4) == 0)
		r = z_env(g_data.env);
	else if (ft_strncmp(data.built, "exit", 5) == 0)
		return (z_exit(data, ft_atoi(data.input)));
	return (ft_error(r));
}

int	lexer(char *input, char **env)
{
	t_cmd	data; /* a changer de nom*/
	int		i;

	//if (ft_strcmp(input, "exit") == 0)
		//exit_msg(input);
	data.input = input;
	//data.rawinput = input;
	data.path = ft_strdup(g_data.pwd);
	data = parse(data);
	i = builtincheck(data, env);
	return (0);
}

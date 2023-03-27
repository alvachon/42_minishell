/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:25 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/27 09:23:57 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtincheck(t_cmd data, char **env)
{
	if (ft_strncmp(data.built, "echo", 5) == 0)
		z_echo(data, env);
	else if (ft_strncmp(data.built, "cd", 3) == 0)
		z_cd(data, env);
	else if (ft_strncmp(data.built, "pwd", 4) == 0)
		z_pwd(env);
	/*else if (ft_strncmp(data.built, "export", 7) == 0)  export a=Hello
		z_export("declare -x", env);*/
	/*else if (ft_strncmp(data.built, "unset", 6) == 0) unset varname
		z_unset();*/
	else if (ft_strncmp(data.built, "env", 4) == 0)
		z_env(env);
	return (0);
}

int	lexer(char *input, char **env)
{
	t_cmd	data;
	int		i;

	if (ft_strcmp(input, "exit") == 0)
		exit_msg(input);
	data.input = input;
	data.path = g_data.pwd;
	data = parse(data);
	i = builtincheck(data, env);
	return (0);
}

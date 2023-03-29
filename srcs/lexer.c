/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:25 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/29 16:14:40 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	builtincheck(t_cmd *data, char **env)
{
	int	r;

	r = 0;
	if (ft_strncmp(data->built, "echo", 5) == 0)
		z_echo(data);
	else if (ft_strncmp(data->built, "cd", 3) == 0)
		r = z_cd(data, g_data.env);
	else if (ft_strncmp(data->built, "pwd", 4) == 0)
		z_pwd(env);
	else if (ft_strncmp(data->built, "export", 7) == 0)
		z_export(data->print);
	else if (ft_strncmp(data->built, "unset", 6) == 0)
		z_unset(data->print);
	else if (ft_strncmp(data->built, "env", 4) == 0)
		z_env(g_data.env);
	return (0);
}

int	lexer(char *input, char **env)
{
	t_cmd	data; /* a changer de nom*/
	int		i;

	if (ft_strcmp(input, "exit") == 0)
		exit_msg(input);
	data.input = input;
	data.path = set("PWD=", 4);
	parse(&data);
	i = builtincheck(&data, env);
	return (0);
}

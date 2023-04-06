/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:25 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/06 11:03:20 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	parse(t_cmd data)
{
	int	i;

	i = 0;
	while (1)
	{
		keep_builtin(i, &data);
		keep_option(&data);
		keep_print(i, &data);
		keep_redir_input(&data);
		/*input = keep_redir_input(input, i);
		input = keep_flag_delim(input, i);
		//input = keep_delimiter(input, i);
		printf("parse : %s\n", input);*/
		return (data);
	}
}

int	ft_error(int code)
{
	if (code > 0)
		perror("Error:");
	return (code);
}

void	data_free(t_cmd *data)
{
	if (data->built)
		free (data->built);
	if (data->path)
		free (data->path);
	return ;
}

int	builtincheck(t_cmd data, char **env)
{
	int	r;

	r = 0;
	if (ft_strncmp(data.built, "echo", 5) == 0)
		r = z_echo(data, g_data.env);
	else if (ft_strncmp(data.built, "cd", 3) == 0)
		r = z_cd(data);
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
	data_free(&data);
	return (ft_error(r));
}

int	lexer(char *input, char **env)
{
	t_cmd	data;
	int		i;

	data.input = input;
	data.path = ft_calloc(1, sizeof(char));
	data = parse(data);
	i = builtincheck(data, env);
	return (0);
}

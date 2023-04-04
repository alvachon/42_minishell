/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:34:26 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/03 13:24:30 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 UTILS - Isolate a chosen data array from our collected env path */
char	*set(int code)
{
	int		i;

	i = 0;
	if (code == 1)
	{
		while (g_data.env[i] && ft_strncmp(g_data.env[i], "PWD=", 4) != 0)
			i++;
	}
	else if (code == 2)
	{
		while (g_data.env[i] && ft_strncmp(g_data.env[i], "HOME=", 5) != 0)
			i++;
	}
	return (g_data.env[i]);
}

void	option(t_cmd *data, char *option, int trigger, int trim_size)
{
	data->opt = option;
	if (strcmp(option, "FIND") == 0)
		remake_path(data);//
	if (strcmp(option, "DIRECT") == 0)
		hard_path(data);//
	if (trigger == 1)
	{
		data->input = wordtrim(data->input, trim_size);
		data->input = ltrim(data->input);
	}
}

void	remake_path(t_cmd *data)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (c != 3)
	{
		if (data->path[i] == '/')
			c++;
		i++;
	}
	data->input++;
	while (data->input)
	{
		if (data->input[0] == '\0')
			break ;
		data->path[i - 1] = data->input[0];
		data->input++;
		i++;
	}
	data->path[i] = '\0';
}

void	hard_path(t_cmd *data)
{
	int	i;

	i = 0;
	while (data->input[0] != '|' || data->input[0] != '<' || \
		data->input[0] != '>')
	{
		if (data->input[0] == '\0')
			break ;
		data->path[i] = data->input[0];
		data->input++;
		i++;
	}
	data->path[i] = '\0';
}

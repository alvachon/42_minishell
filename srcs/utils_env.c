/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:34:26 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/31 13:26:57 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 UTILS - Isolate a chosen data array from our collected env path */
char	*set(char *var, int siz_var)
{
	int		i;
	char	**cmd;
	char	*file;

	i = 0;
	while (ft_strncmp(var, g_data.env[i], siz_var) != 0)
		i++;
	cmd = ft_split(g_data.env[i], ':');
	file = ft_substr(cmd[0], siz_var, ft_strlen(file));
	i = 0;
	while (cmd[i] != NULL)
	{
		free(cmd[i]);
		i++;
	}
	free(cmd);
	return (file);
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
	while (data->input[0] != '|' || data->input[0] != '<' || \
		data->input[0] != '>')
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:34:26 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/27 14:54:49 by alvachon         ###   ########.fr       */
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
	file = cmd[0];
	file = ft_substr(file, siz_var, ft_strlen(file));
	free(cmd);
	return (file);
}

void	option(t_cmd *data, char *option, int trigger, int trim_size)
{
	data->opt = option;
	if (strcmp(option, "FIND") == 0)
		remake_path(data);
	if (strcmp(option, "DIRECT") == 0)
		hard_path(data);
	if (trigger == 1)
	{
		data->input = wordtrim(data->input, trim_size);
		data->input = ltrim(data->input);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/03/29 16:28:00 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	delete_last(t_cmd *data)
{
	char	*str;
	int		i;
	int		c;

	i = 0;
	str = data->path;
	printf("last : %s\n", data->path);
	while (str[i])
		i++;
	c = i;
	while (str[i] != '/')
		i--;
	return (c - i);
}

void	rewrite(t_cmd *data, int i)
{
	int	j;

	j = 0;
	while (data->path[j])
		j++;
	j -= i;
	i = 0;
	while (i < j)
		i++;
	data->path[i] = '\0';
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

void	keep_user(t_cmd *data)
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
	data->path[i - 1] = '\0';
}

int	z_cd(t_cmd *data, char **env)
{
	char	*temp;
	int		i;

	i = 0;
	if (strcmp(data->opt, "BACK") == 0)
		rewrite(data, delete_last(data));
	if (strcmp(data->opt, "STAY") == 0 || strcmp(data->opt, "FIND") == 0)
		data->path = data->path;
	if (strcmp(data->opt, "HOME") == 0)
		keep_user(data);
	/*if (strcmp(data->opt, "DIRECT") == 0)
		data->path = data->print;*/
	chdir(data->path);
	if (data->path[0] == '\0')
		data->path[0] = '/';
	while (env[i] && ft_strncmp(env[i], "PWD=", 4) != 0)
		i++;
	temp = ft_substr(env[i], 4, ft_strlen(env[i]));
	env[i] = ft_strjoin("PWD=", data->path);
	while (env[i] && ft_strncmp(env[i], "OLDPWD=", 7) != 0)
		i++;
	env[i] = ft_strjoin("OLDPWD=", temp);
	free(temp);
	return (errno);
}

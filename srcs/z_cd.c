/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_cd.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2023/04/05 18:39:58 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strpaste(char *already_here, char *new)
{
	unsigned int	i;
	unsigned int	j;
	char			*fusion;

	i = 0;
	j = 0;
	if (!new)
		return (NULL);
	if (!already_here)
		return (new);
	fusion = ft_calloc((ft_strlen(already_here) + ft_strlen(new)) + 1, \
		sizeof(char));
	if (!fusion)
		return (NULL);
	if (ft_strlen(already_here) == 1 && already_here[0] == '/' && new[0] == '/')
		new++;
	while (already_here[i] != '\0')
	{
		fusion[i] = already_here[i];
		i++;
	}
	while (new[j] != '\0')
	{
		fusion[i + j] = new[j];
		j++;
	}
	fusion[i + j] = '\0';
	if (already_here)
		free(already_here);
	return (fusion);
}

void	remove_section(t_cmd *data)
{
	int		index;
	char	*temp;

	index = 0;
	if (data->path[ft_strlen(data->path) - 1] == '/')
		index = 1;
	while (data->path[ft_strlen(data->path) - index - 1] != '/')
		index++;
	index = ft_strlen(data->path) - index;
	temp = ft_substr(data->path, 0, index);
	free(data->path);
	data->path = ft_strdup(temp);
	index = 2;
	while (index--)
		data->input++;
	free(temp);
}

void	add_section(t_cmd *data)
{
	int		i;
	char	*buff;

	i = 0;
	i = chartrim(data->input, '/');
	if (i == 0)
		i = 1;
	buff = ft_substr(data->input, 0, i);
	if (buff[0] == '/' && data->path[ft_strlen(data->path) - 1] == '/')
	{
		free (buff);
		data->input++;
		return ;
	}
	data->path = ft_strpaste(data->path, buff);
	while (i--)
		data->input++;
	if (buff != NULL)
		free(buff);
}

void	do_relative_path(t_cmd *data)
{
	data->path = ft_strpaste(data->path, g_data.pwd);
	if (data->path[ft_strlen(data->path) - 1] != '/')
		data->path = ft_strpaste(data->path, "/");
	while (data->input[0] == '/' || ft_isalnum(data->input[0]) == 1 || \
		ft_strncmp(data->input, "..", 2) == 0)
	{
		if (data->input[0] == '/' || ft_isalnum(data->input[0]) == 1)
			add_section(data);
		else if (ft_strncmp(data->input, "..", 2) == 0)
			remove_section(data);
		if (ft_strncmp(data->input, "./", 2) == 0)
			data->input += 2;
	}
}

void	do_direct_path(t_cmd *data)
{
	while (data->input[0] == '/' || ft_isalnum(data->input[0]) == 1 || \
		ft_strncmp(data->input, "..", 2) == 0)
	{
		if (data->input[0] == '/' || ft_isalnum(data->input[0]) == 1)
			add_section(data);
		else if (ft_strncmp(data->input, "..", 2) == 0)
			remove_section(data);
		if (ft_strncmp(data->input, "./", 2) == 0)
			data->input += 2;
	}
}

int	z_cd(t_cmd data)
{
	char	*temp;
	char	*temp2;
	int		i;

	i = 0;
	i = chdir(data.path);
	if (i == -1)
		return (errno);
	temp = ft_strjoin("OLDPWD=", g_data.pwd);
	z_export(temp);
	free (g_data.pwd);
	if (data.path[ft_strlen(data.path) - 1] == '/')
	{
		temp2 = ft_substr(data.path, 0, ft_strlen(data.path) - 1);
		g_data.pwd = ft_strdup (temp2);
		free (temp2);
	}
	else
		g_data.pwd = ft_strdup(data.path);
	free (temp);
	temp = ft_strjoin("PWD=", g_data.pwd);
	z_export(temp);
	free(temp);
	return (errno);
}

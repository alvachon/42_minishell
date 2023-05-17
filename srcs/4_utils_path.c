/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4_utils_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 10:58:10 by fboulang          #+#    #+#             */
/*   Updated: 2023/05/16 10:59:19 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Function to set file access and read data*/
int	set_file(int file, char *temp, t_node *node)
{
	char	*read;

	if (file == -1)
	{
		free(temp);
		node->job.in = file;
		return (1);
	}
	if (ft_strncmp(node->job.built, "cd", 2) == 0)
	{
		read = ft_readline(file, 1, NULL);
		node->job.path = ft_strdup(read);
		free (read);
		close (file);
	}
	else if (builtin_check(node) != 0)
		node->job.in = file;
	free(temp);
	return (0);
}

/*Function that join strings and free data*/
char	*ft_strpaste(char *ah, char *new)
{
	t_in			ind;
	char			*fusion;

	ind = init_ind();
	if (!ah)
		return (new);
	fusion = ft_calloc((ft_strlen(ah) + ft_strlen(new)) + 1, sizeof(char));
	if (!fusion || !new)
		return (NULL);
	if (ft_strlen(ah) == 1 && ah[0] == '/' && new[0] == '/')
		new++;
	while (ah[ind.i] != '\0')
	{
		fusion[ind.i] = ah[ind.i];
		ind.i++;
	}
	while (new[ind.j] != '\0')
	{
		fusion[ind.i + ind.j] = new[ind.j];
		ind.j++;
	}
	fusion[ind.i + ind.j] = '\0';
	if (ah)
		free(ah);
	return (fusion);
}

void	do_relative_path(t_node *node)
{
	node->job.path = ft_strpaste(node->job.path, g_data.pwd);
	if (node->job.path[ft_strlen(node->job.path) - 1] != '/')
		node->job.path = ft_strpaste(node->job.path, "/");
	while (node->job.temp[0] == '/' || ft_isalnum(node->job.temp[0]) == 1 || \
			ft_strncmp(node->job.temp, "..", 2) == 0)
	{
		if (node->job.temp[0] == '/' || ft_isalnum(node->job.temp[0]) == 1)
			add_section(node);
		else if (ft_strncmp(node->job.temp, "..", 2) == 0)
			remove_section(node);
		if (ft_strncmp(node->job.temp, "./", 2) == 0)
			node->job.temp += 2;
	}
}

void	do_direct_path(t_node *node)
{
	while (node->job.temp[0] == '/' || ft_isalnum(node->job.temp[0]) == 1 || \
			ft_strncmp(node->job.temp, "..", 2) == 0)
	{
		if (node->job.temp[0] == '/' || ft_isalnum(node->job.temp[0]) == 1)
			add_section(node);
		else if (ft_strncmp(node->job.temp, "..", 2) == 0)
			remove_section(node);
		if (ft_strncmp(node->job.temp, "./", 2) == 0)
			node->job.temp += 2;
	}
}

void	do_home_path(t_node *node)
{
	free(node->job.path);
	node->job.path = ft_strdup(g_data.home);
	return ;
}

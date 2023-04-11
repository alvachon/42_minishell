/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   z_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:22:05 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/05 18:51:51 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*add_content(char *content, char *add, int position)
{
	char	*mod;
	int		i;
	int		j;
	int		k;

	i = -1;
	j = 0;
	k = 0;
	mod = ft_calloc(1, (ft_strlen(content) - 1) + ft_strlen(add));
	while (1)
	{
		while (i++ != position)
			mod[i] = content[i];
		k = i + 1;
		while (add[j])
			mod[i++] = add[j++];
		while (content[k] > 32)
			k++;
		while (content[k])
			mod[i++] = content[k++];
		break ;
	}
	mod[i] = '\0';
	return (mod);
}

void	do_guil(t_cmd *data, int i)
{
	char	c;

	c = data->input[0];
	data->input++;
	i = chartrim(data->input, c);
	data->print = ft_substr(data->input, 0, i);
	while (i-- + 1)
		data->input++;
}

void	do_sp(t_cmd *data, int i)
{
	i = token_reach(i, data->input);
	data->print = ft_substr(data->input, 0, i);
	while (i-- && *data->input != '\0')
		data->input++;
}

void	do_ref(t_cmd *data, int i)
{
	int		j;
	char	*paste_env;

	i = chartrim(data->print, '$');
	j = i;
	while (data->print[j])
	{
		if (data->print[j] <= 32)
			break ;
		j++;
	}
	j -= i;
	paste_env = ft_substr(data->print, i, j);
	paste_env = repurpose(paste_env, 1);
	paste_env = print_var(paste_env);
	if (paste_env[0] == '\0')
		data->print = repurpose(data->print, 0);
	else
		data->print = add_content(data->print, paste_env, i);
}

int	z_echo(t_cmd data, char **env)
{
	(void)env;
	if (ft_strncmp(data.opt, "-n", 2) == 0)
		printf("%s", data.print);
	else
		printf("%s\n", data.print);
	return (errno);
}

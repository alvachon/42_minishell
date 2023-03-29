/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_in_progress.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:17:01 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/29 15:48:13 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	keep_redir_input(t_cmd *data, int i)
{
	if (data->input[0] == '<' && data->input[1] == '<')
	{
		data->redir_input = ft_substr(data->input, 0, 2);
		i = 2;
	}
	if (data->input[0] == '>' && data->input[1] == '>')
	{
		data->redir_input = ft_substr(data->input, 0, 2);
		i = 2;
	}
	if (data->input[0] == '<' && data->input[1] <= 32)
	{
		data->redir_input = ft_substr(data->input, 0, 1);
		i = 1;
	}
	if (data->input[0] == '>' && data->input[1] <= 32)
	{
		data->redir_input = ft_substr(data->input, 0, 1);
		i = 1;
	}
	data->input = wordtrim(data->input, i);
	data->input = ltrim(data->input);
}

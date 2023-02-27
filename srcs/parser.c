/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:14:08 by alvachon          #+#    #+#             */
/*   Updated: 2023/02/23 15:14:09 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	keep_redir_input(t_cmd data, int i)
{
	(void)i;//
	if (data.input[0] == '<' && data.input[1] <= 32)
	{
		data.redir_input = ft_substr(data.input, 0, 1);
		data.input++;
		data.input = ltrim(data.input);
	}
}

void	keep_flag_delim(t_cmd data, int i)
{
	if (data.input[0] == '<' && data.input[1] == '<')
	{
		data.flag_delim = ft_substr(data.input, 0, 2);
		i = 2;
		data.input = wordtrim(data.input, i);
		data.input = ltrim(data.input);
	}
}

t_cmd	parse(t_cmd data)
{
	int i;

	i = 0;
	while (1)
	{
		keep_builtin(i, &data);//check for redir symbol before
		keep_option(i, &data);
		keep_print(i, &data);
		printf("built int : %s\n", data.built);
		printf("opt : %s\n", data.opt);
		printf("print : %s\n", data.print);
		/*input = keep_redir_input(input, i);
		input = keep_flag_delim(input, i);
		//input = keep_delimiter(input, i);
		printf("parse : %s\n", input);*/
		return (data);
	}
}
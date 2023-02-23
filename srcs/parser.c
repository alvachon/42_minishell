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


char *keep_redir_input(char *input, int i)
{
	(void)i;//
	if (input[0] == '<' && input[1] <= 32)
	{
		g_data.input.redir_input = ft_substr(input, 0, 1);
		input++;
		input = ltrim(input);
	}
	return (input);
}

char *keep_flag_delim(char *input, int i)
{
	if (input[0] == '<' && input[1] == '<')
	{
		g_data.input.flag_delim = ft_substr(input, 0, 2);
		i = 2;
		input = wordtrim(input, i);
		input = ltrim(input);
	}
	return (input);
}

char *parse(char *input)
{
	int i;

	i = 0;
	while (*input)
	{
		input = keep_builtin(input, i);//check for redir symbol before
		input = keep_option(input, i);
		input = keep_print(input, i);
		/*input = keep_redir_input(input, i);
		input = keep_flag_delim(input, i);
		//input = keep_delimiter(input, i);
		printf("parse : %s\n", input);*/
		break ;
	}
	return (input);
}
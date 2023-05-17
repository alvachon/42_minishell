/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_expand.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:25 by alvachon          #+#    #+#             */
/*   Updated: 2023/05/16 09:08:49 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Function to reach the assigned value and return it as the keyword*/
char	*print_var(char *str)
{
	char	*temp;
	int		i;

	i = 0;
	if (ft_strncmp(str, "?=", 2) == 0)
	{
		temp = ft_itoa(g_data.retval);
		free(str);
		return (temp);
	}
	while (g_data.env[i] && ft_strncmp(g_data.env[i], str, ft_strlen(str)) != 0)
		i++;
	if (g_data.env[i] != NULL)
		temp = ft_substr(g_data.env[i], ft_strlen(str),
				ft_strlen(g_data.env[i]));
	else
		temp = ft_calloc(1, sizeof(char));
	free(str);
	return (temp);
}

/*Function to remove association token on the assigned value*/
char	*repurpose(char *str, int code)
{
	int		i;
	char	*new_str;

	i = 0;
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (code == 0)
	{
		while (str[i] != '$')
			i++;
	}
	while (str[i + 1] != '\0')
	{
		new_str[i] = str[i + 1];
		i++;
	}
	new_str[i] = '=';
	i++;
	new_str[i] = '\0';
	free(str);
	return (new_str);
}

/*Function to remove the token if no assigned value*/
char	*rm_ref(char *input, int i, int l)
{
	int		j;
	int		k;
	int		s;
	char	*phrase;

	j = 0;
	k = 0;
	s = l - i;
	phrase = ft_calloc(ft_strlen(input) - (l - i) + 1, sizeof(char));
	while (input[k] != '\0')
	{
		if (j == i)
			k = l;
		phrase[j] = input[k];
		j++;
		k++;
	}
	phrase[j] = '\0';
	free(input);
	return (phrase);
}

/*Function to replace the token by the assigned value*/
char	*find_expand(int i, char *input)
{
	int		l;
	char	*str;
	char	*keyword;

	l = i;
	while (input[l] > 32 && input[l] != 34 && input[l] != '=' && input[l] != 39)
	{
		l++;
		if (input[l] == '$' || (input[l] == '?' && (l - i) == 1))
		{
			if (input[l] == '?' && (l - i) == 1)
				l++;
			break ;
		}
	}
	str = ft_substr(input, i, l - i);
	keyword = print_var(repurpose(str, 1));
	str = ft_substr(input, i, l - i);
	if (!*keyword)
		input = rm_ref(input, i, l);
	else
		input = add_content(input, keyword, i, str);
	free(keyword);
	free(str);
	return (input);
}

/*Control function for verify if they are expand token*/
char	*check_expand(int i, char *input)
{
	while (input[i] != '\0')
	{
		while (input[i] == '$')
		{
			if (input[i] == '$' && input[i + 1] == '\0')
				break ;
			if (input[i] == '$' && input[i + 1] == ' ')
				break ;
			if (input[i] == '$' && input[i + 1] == '=')
				break ;
			if (input[i] == '$' && (input[i + 1] == 34))
				break ;
			input = find_expand(i, input);
		}
		if (input[i] == 39)
		{
			i = skip_simple_guil(i, input);
			if (input[i] == '\0')
				break ;
			else
				continue ;
		}
		i++;
	}
	return (input);
}

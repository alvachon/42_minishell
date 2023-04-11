/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:27:43 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/05 20:21:39 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
Find a specific ascii char as trigger system*/
int	scan(char *input, char c)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == c)
			return (0);
		i++;
	}
	return (1);
}

/*
Return a strlen until a specific reach */
int	chartrim(char *input, char c)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(input);
	if (scan(input, c) == 1)
		return (len);
	while (input[i] != c && input[i] != '\0')
	{
		i++;
		len--;
	}
	return (i);
}

char *repurpose(char *str, int code)
{
	int i;
	char *copy;

	i = 0;
	copy = str;
	if (code == 0)
	{
		while (str[i] != '$')
			i++;
	}
	while (str[i + 1] != '\0')
	{
		str[i] = copy[i + 1];
		i++;
	}
	if (code == 1)
		str[i] = '=';
	else
		str[i] = '\0';
	return (str);
}

char	*print_var(char *var)
{
	char	*temp;
	int		i;

	i = 0;
	while (g_data.env[i] && ft_strncmp(g_data.env[i], var, ft_strlen(var)) != 0)
		i++;
	if (g_data.env[i] != NULL)
		temp = ft_substr(g_data.env[i], ft_strlen(var), \
			ft_strlen(g_data.env[i]));
	else
		temp = "\0";
	return (temp);
}

int	token_reach(int i, char *str)
{
	if (!str)
		return (0);
	i = chartrim(str, '|');
	if (i > chartrim(str, '<'))
		i = chartrim(str, '<');
	if (i > chartrim(str, '>'))
		i = chartrim(str, '>');
	return (i);
}

int distance_finder(t_cmd *data)
{
	int i;

	i = 0;
	while (data->input[i] != '\0')
	{
		if ((data->input[i] == 34 || data->input[i] == 39) && i == 0)
			i = 1;
		else if ((data->input[i] == 34 || data->input[i] == 39) && i == 1)
			i = 0;
		if (i == 0 &&
		(data->input[i] == '|' || data->input[i] == '>' ||
			data->input[i] == '<'))
			return (i);
		i++;
	}
	return (i);
}

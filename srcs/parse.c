/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:14:08 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/03 13:18:23 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	keep_print(int i, t_cmd *data)
{
	if (data->input[0] != '<' || data->input[0] != '>'
		|| data->input[0] != '|')
	{
		if (data->input[0] == 34)
			trim_guil(&data, 34, 0);
		else if (data->input[0] == 39)
			trim_guil(&data, 39, 0);
		else
			trim_guil(&data, 0, 1);
	}
	i = ft_strlen(data->print);
	while (i)
	{
		data->input++;
		i--;
	}
}

char	*ft_strpaste(char const *s1, char const *s2)
{
	unsigned int	i;
	unsigned int	j;
	char			*s3;

	i = 0;
	j = 0;

	printf("s1 :%s\n", s1);
	printf("s2 :%s\n", s2);
	if (!s1 && !s2)
		return (NULL);
	s3 = ft_calloc ((ft_strlen(s1) + ft_strlen(s2)) + 1, sizeof (char));
	if (!s3)
		return (NULL);
	while (s1[i] != '\0')
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		s3[i + j] = s2[j];
		j++;
	}
	s3[i + j] = '\0';
	if (s1)
		free((char *)s1);
	printf("s3 :%s\n", s3);
	return (s3);
}

/*
temp = ft_substr
buff = ft_strpaste(buff, temp)
free (temp)*/



void	keep_option(t_cmd *data)
{
	int		i;
	char	*temp;
	char	*buff;//path ou input

	i = 0;
	if (strcmp(data->built, "echo") == 0 && strncmp(data->input, "-n ", 3) == 0)
		option(data, "-n", 1, 2);
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "..", 2) == 0)
	{
		option(data, "BACK", 1, 2);
		return ;
	}
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, ".", 1) == 0)
	{
		option(data, "STAY", 1, 1);
		return ;
	}
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "/", 1) == 0)
	{
		/* si '.' -> avance, free temp, ignore  */
		//work with absolu (input)
		//data->input++;
		buff = ft_substr(data->input, 0, 1);
		data->input++;
		i = chartrim(data->input, '/') + 1;
		temp = ft_substr(data->input, 0, i);
		if (ft_strncmp(temp, "..", 2) == 0 && ft_strncmp(data->input, "..", 2) == 0)
		{
			free(temp);
			option(data, "", 1, 2);//chnager option trigger plus tard
		}
		buff = ft_strpaste(buff, temp);
		free (temp);
		while (i--)
			data->input++;
		i = chartrim(data->input, '/');
		printf("buff :%s\n", buff);
		printf("inpu :%s\n", data->input);
		exit(0);
	}
	/*if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "../", 3) == 0)
	{
		option(data, "BACK", 1, 0);
		data->input[0] = '~';
		keep_option(data);
	}*/
	/*if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "./", 2) == 0)
	{
		option(data, "STAY", 1, 1);
		keep_option(data);
	}*/
	/*if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "~/", 2) == 0)
		option(data, "FIND", 1, 0); tilde = var home*/
	/*if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "/", 1) == 0)
		option(data, "DIRECT", 0, 0);*/
	/*else if (strcmp(data->built, "cd") == 0)
		option(data, "HOME", 0, 0);//bug here*/
}

void	keep_builtin(int i, t_cmd *data)
{
	char	*str;

	data->input = ltrim(data->input);
	i = wordlen(data->input, i);
	str = ft_substr(data->input, 0, i);
	str = ulstr(str);//echo seulement
	str = trimchar(str, 32);
	data->built = ft_strdup(str);
	free (str);
	data->input = wordtrim(data->input, i);
	data->input = ltrim(data->input); //echo hello < world -> must not work.
}

t_cmd	parse(t_cmd data)
{
	int	i;

	i = 0;
	while (1)
	{
		keep_builtin(i, &data);
		keep_option(&data);
		keep_print(i, &data);
		/*input = keep_redir_input(input, i);
		input = keep_flag_delim(input, i);
		//input = keep_delimiter(input, i);
		printf("parse : %s\n", input);*/
		return (data);
	}
}

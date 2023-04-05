/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 15:14:08 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/05 16:47:45 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
	data->input : "allo", 'allo', allo allo allo, allo"allo allo"allo
	note : $
	1. Envoyer le data dans print, tasser data-input;

	2. dans data->print, checker pour les $
	3. si oui, mettre le mot temporaire dans la ft temp.
	4. Modifier le mot en ajoutant un = la fin et enlever le $
	5. Checker si le mot est dans env,
		si oui : Print le mot
		si non : pass;
	6. a la fin, trim guil
	7 : set la donnee dans print.
*/

int	token_reach(int i, char *str)
{
	i = chartrim(str, '|');
	if (i > chartrim(str, '<'))
		i = chartrim(str, '<');
	if (i > chartrim(str, '>'))
		i = chartrim(str, '>');
	return (i);
}

int	sp_token_reach(int i, char *str)
{
	i = token_reach(i, str);
	if (i > chartrim(str, ' '))
		i = chartrim(str, ' ');
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

char	*add_content(char *content, char *add, int position)
{
	char *mod;
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	mod = ft_calloc(1, (ft_strlen(content) - 1) + ft_strlen(add));
	while (1)
	{
		while (i != position)
		{
			mod[i] = content[i];
			i++;
		}
		k = i + 1;
		while (add[j])
		{
			mod[i] = add[j];
			i++;
			j++;
		}
		while (content[k] > 32)
			k++;
		while (content[k])
		{
			mod[i] = content[k];
			i++;
			k++;
		}
		break ;
	}
	mod[i] = '\0';
	content = mod;
	return (content);
}

void	keep_print(int i, t_cmd *data)
{
	char c;
	char *paste_env;
	int j;

	c = data->input[0];
	if (data->input[0] == 34 || data->input[0] == 39)
	{
		data->input++;
		i = chartrim(data->input, c);
		data->print = ft_substr(data->input, 0, i);
		while (i-- + 1)
			data->input++;
	}
	else
	{
		i = token_reach(i, data->input);
		data->print = ft_substr(data->input, 0, i);
		while (i--)
			data->input++;
	}
	while (scan(data->print, '$') == 0)
	{
		i = chartrim(data->print, '$');
		j = i;
		while (data->print[j])
		{
			if (data->print[j] == 32)
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
}

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
	fusion = ft_calloc((ft_strlen(already_here) + ft_strlen(new)) + 1, sizeof(char));
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

void	keep_option(t_cmd *data)
{
	int i;

	i = 0;
	if (strcmp(data->built, "echo") == 0 && strncmp(data->input, "-n ", 3) == 0)
		option(data, "-n", 1, 2);
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "/", 1) != 0)
	{
		data->path = ft_strpaste(data->path, g_data.pwd);
		if (data->path[ft_strlen(data->path) - 1] != '/')
			data->path = ft_strpaste(data->path, "/");
		while (data->input[0] == '/' || ft_isalnum(data->input[0]) == 1 || ft_strncmp(data->input, "..", 2) == 0)
		{
			if (data->input[0] == '/' || ft_isalnum(data->input[0]) == 1)
				add_section(data);
			else if (ft_strncmp(data->input, "..", 2) == 0)
				remove_section(data);
			if (ft_strncmp(data->input, "./", 2) == 0)
				data->input += 2;
			printf("%s\n", data->path);
		}
	}
	if (strcmp(data->built, "cd") == 0 && strncmp(data->input, ".", 1) == 0)
	{
		option(data, "STAY", 1, 1);
		return ;
	}
	if (strcmp(data->built, "cd") == 0 && (strncmp(data->input, "/", 1) == 0))
	{
		while (data->input[0] == '/' || ft_isalnum(data->input[0]) == 1 || ft_strncmp(data->input, "..", 2) == 0)
		{
			if (data->input[0] == '/' || ft_isalnum(data->input[0]) == 1)
				add_section(data);
			else if (ft_strncmp(data->input, "..", 2) == 0)
				remove_section(data);
			if (ft_strncmp(data->input, "./", 2) == 0)
				data->input += 2;
			printf("%s\n", data->path);
		}
	}
	/*if (strcmp(data->built, "cd") == 0 && strncmp(data->input, "./", 2) == 0)
	{
		option(data, "STAY", 1, 1);
		keep_option(data);
	}*/
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

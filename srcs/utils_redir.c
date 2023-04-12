/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 12:03:12 by alvachon          #+#    #+#             */
/*   Updated: 2023/04/12 13:33:27 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// po sur
void	ft_swipe(t_cmd *data)
{
	int		i;
	int		j;
	char	*str;

	i = 2;
	j = 0;
	str = ft_calloc(1, sizeof(char) * ft_strlen(data->input));
	if (!str)
		return ; //
	while (data->input[i] > 32 && data->input)
		str[j++] = data->input[i++];
	str[j] = ' ';
	j++;
	str[j] = '<';
	j++;
	while (data->input[i] != '\0')
		str[j++] = data->input[i++];
	str[j] = '\0';
	data->input = ft_strdup(str);
	free(str);
}

/*should return a value for error management ...*/
void	do_input(int i, t_cmd *data)
{
	int		file;
	char	*read;

	data->input += 2;
	data->input = ltrim(data->input);
	/*if (data->fd != 0)
		do();*/
	file = open(ft_substr(data->input, 0, wordlen(data->input, i)), O_RDONLY);
	if (file == -1)
		return ;
	while (data->input[0] > 32 && data->input[0] != '\0')
		data->input++;
	data->input = ltrim(data->input);
	read = ft_readline(file, 1, NULL);
	if (ft_strcmp(data->built, "cd") == 0)
		data->path = read;
	else
		data->print = read;
	close(file);
	data->input = ltrim(data->input);
}

/*should return a value for error management ...*/
void	do_heredoc(int i, t_cmd *data)
{
	char	*delim;
	char	*cmd;

	//int		file;
	//char	*read;
	data->input += 3;
	data->input = ltrim(data->input);
	/*if (data->fd != 0)
		do();*/
	/*file = open(ft_substr(data->input, 0, wordlen(data->input, i)), O_RDONLY);
	if (file == -1)
		return ;
	while (data->input[0] > 32 && data->input[0] != '\0')
		data->input++;
	data->input = ltrim(data->input);*/
	delim = ft_substr(data->input, 0, wordlen(data->input, i));
	cmd = NULL;
	while (1)
	{
		cmd = readline("> ");
		if (!cmd)
			ctrl_c_eof();
		if (ft_strncmp(cmd, delim, ft_strlen(delim)) == 0)
			break ;
		if (cmd[0] == '\0' || ft_strcmp(cmd, "\n") == 0)
			continue ;
		else if (lexer(cmd, g_data.env) > 0) //po sur
			break ;
		free(cmd);
	}
}

/*should return a value for error management ...*/
/*void	do_output(int i, t_cmd *data)
{
	int		file;
	char	*print;

	data->input += 2;
	data->input = ltrim(data->input);
	//if (data->fd != 0)
	//	do();
	file = open(ft_substr(data->input, 0, wordlen(data->input, i)), O_WRONLY, \
			O_CREAT | O_TRUNC);
	if (file == -1)
		return ;
	while (data->input[0] > 32 && data->input[0] != '\0')
		data->input++;
	data->input = ltrim(data->input);
	print = ft_result();
	write(file, print, ft_strlen(print));
	close(file);
	data->input = ltrim(data->input);
}*/

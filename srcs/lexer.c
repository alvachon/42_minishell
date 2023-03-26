/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:14:25 by alvachon          #+#    #+#             */
/*   Updated: 2023/03/26 15:56:48 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* [0]BUILT [1]OPTION [2]REDIRECTION [3]APPEND [4]INFILE
* [5]PIPE [6]REDIRECTION [7]APPEND [8]OUTFILE */

#include "../includes/minishell.h"

/*void	nulldata(t_cmd *data)
{
	data->built = NULL;
	data->flag_delim = NULL;
	data->input = NULL;
	data->opt = NULL;
	data->path = NULL;
	data->print = NULL;
	data->redir_input = NULL;
}*/

int	builtincheck(t_cmd data, char **env)
{
	int		i;

	i = 7;
	if (ft_strncmp(data.built, "echo", 5) == 0)
		z_echo(data, env);
	else if (ft_strncmp(data.built, "cd", 3) == 0)
		z_cd(data, env);
	else if (ft_strncmp(data.built, "pwd", 4) == 0)
		z_pwd(env);
	/*else if (ft_strncmp(data.built, "export", 7) == 0)
		z_export(data, env)*/
	else if (ft_strncmp(data.built, "unset", 6) == 0)
		i = 5;
	else if (ft_strncmp(data.built, "env", 4) == 0)
		i = 6;
	//nulldata(&data);
	if (i <= 6)
		return (i);
	/*else
		return (envcheck(data.built));*/
	return (0);
}

char	**paths_search(void)//vers brew bin
{
	int	i;

	i = 0;
	while (ft_strncmp("PATH=", g_data.env[i], 5) != 0)
		i++;
	return (ft_split(g_data.env[i], ':'));
}

/*
! Confirm with JU what to do with the exit function in the lexer ... [ ]
! Verify the error management if the implementation is still logic [ ]
! Verifiy if segemented data is parsed or not [ ]
 Lexer Step :
	1. Take the input as it is and put it in the struct
	2. Isolate the path from env with paht_search();
	3. Return a struct with segmented data (parser.c)
	4. Check if first called built in if from one of our asked implementation
		 If not, free and return 1 (I think its for error ...)
		 If yes, will parse the built in ...
*/

int	lexer(char *input, char **env)
{
	t_cmd	data;
	int		i;

	if (ft_strcmp(input, "exit") == 0)
		exit_msg(input);
	data.input = input;
	data.path = g_data.pwd;
	data = parse(data);
	i = builtincheck(data, env);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <alvachon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:35:32 by alvachon          #+#    #+#             */
/*   Updated: 2023/05/16 10:57:31 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*Set global data for keep important env directory*/
char	*set(int code)
{
	int	i;

	i = 0;
	if (code == 1)
	{
		while (g_data.env[i] && ft_strncmp(g_data.env[i], "PWD=", 4) != 0)
			i++;
	}
	else if (code == 2)
	{
		while (g_data.env[i] && ft_strncmp(g_data.env[i], "HOME=", 5) != 0)
			i++;
	}
	return (g_data.env[i]);
}

/*Set memory for working env modifications*/
char	**ft_setenv(char **env)
{
	int		i;
	int		j;
	char	**buff;

	i = 0;
	j = -1;
	while (env[i])
		i++;
	buff = ft_calloc(i + 1, sizeof(char *));
	while (++j < i)
		buff[j] = ft_strdup(env[j]);
	buff[j] = NULL;
	return (buff);
}

/*structure for indexation*/
t_in	init_ind(void)
{
	t_in	init;

	init.i = 0;
	init.j = 0;
	init.k = 0;
	return (init);
}

int	ft_errormsg(int code)
{
	if (code == errno)
		return (code);
	if (code == 1)
		write(2, "minishell : incorrect use of a token\n", 38);
	if (code == 2)
		write(2, "minishell : No such file or directory\n", 39);
	if (code == 3)
		write(2, "minishell : exit : numeric argument required\n", 46);
	if (code == 4)
		write(2, "minishell : export : invalid identifier\n", 41);
	if (code == 5)
		write(2, "minishell : command not found\n", 31);
	return (code);
}

/*Print error from errno and return code*/
int	ft_error(int code)
{
	char	*temp;

	temp = ft_itoa(code);
	if (code > 0 && code != 22)
		printf("%s\n", strerror(errno));
	free(temp);
	return (code);
}

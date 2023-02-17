/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvachon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 18:27:43 by alvachon          #+#    #+#             */
/*   Updated: 2023/02/15 18:27:44 by alvachon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	error_msg(char *cmd)
{
	char	**buff;

	buff = ft_split(cmd, ' ');
	write (2, "minishell: ", 12);
	write (2, buff[0], ft_strlen(buff[0]));
	write (2, " : Command not found.\n", 23);
	return ;
}

void    exit_msg(char *cmd, t_terminal *minishell)
{
    if (cmd)
    {
        printf("%s\n", cmd);
	    free(cmd);
    }
    if ((*minishell).term)
	    free((*minishell).term);
    clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &(*minishell).mod_terminal);
    exit(EXIT_SUCCESS);
}

void    sys_msg(char *reason, int code)
{
    if (code == 2)
    {
        perror(reason);
        exit(EXIT_FAILURE);
    }
}

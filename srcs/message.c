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
    ft_freeall(buff);
	return ;
}

void    exit_msg(char *cmd)
{
    if (cmd)
    {
        write(1, "exit\n", 5);
        free(cmd);
    }
    clear_history();
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

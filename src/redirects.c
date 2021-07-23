/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellaca-f <ericllaca@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 13:02:28 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 15:24:24 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	Esto es para debuggear los fds que usamos, cuando lo hayamor revisado
*	borramos este fichero entero.
*/
void	ft_parent_log_open(t_shell *shell, int id, int fd)
{
	if (shell->is_child)
	{
		dprintf(shell->stdout_save, "(%d)abre fd %d\n", id, fd);
	}
}

void	ft_parent_log(t_shell *shell, int id, int fd)
{
	if (shell->is_child)
	{
		dprintf(shell->stdout_save, "(%d)cierra fd %d\n", id, fd);
	}
}

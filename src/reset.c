/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellaca-f <ericllaca@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:55:04 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 15:16:47 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	This function resets the argv part of the shell,
*	it restores the standard file descriptors and set the
*	values to its defaults.
*	shell->args is freed with its own function (arg_clean).
*/
int	reset_argv(t_shell *shell)
{
	if (!shell->is_child)
	{
		dup2(shell->stdin_save, STDIN_FILENO);
		dup2(shell->stdout_save, STDOUT_FILENO);
		dup2(shell->stderr_save, STDERR_FILENO);
		shell->pipe_write = STDOUT_FILENO;
		shell->prev_pipe_read = STDIN_FILENO;
	}
	arg_clean(shell->args);
	shell->args = NULL;
	return (0);
}

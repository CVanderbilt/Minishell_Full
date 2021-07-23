/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellaca-f <ericllaca@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:57:17 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 15:01:09 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"
#include "env_set.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
*	This function its just a wrap of the arg_counter function,
*	if arg_counter raised an error output int of the last program
*	is set to 127, in any case it returns the arg_counter returned value.
*/
int	parser(t_shell *shell, char **line, int pos)
{
	int	h;

	h = arg_counter(shell, *line, pos);
	if (h == -1)
		shell->ret = 127;
	return (h);
}

/*
*	This function returns the function pointer that corresponds with
*	the first argument of the command, if is a builtin function it returns
*	that function, if not it returns the exec function.
*/
void	*get_cmd(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->cmd->cmds[i])
	{
		if (!(ft_strcmp(shell->args->arg, shell->cmd->cmds[i])))
			return (shell->cmd->ms_cmds[i]);
		i++;
	}
	return (shell->cmd->exec);
}

/*
*	This function is the first of a set of functions, despite its name
*	it will parse the line into arguments inside the shell struct,
*	it returns the position where the parsed ended and a negative integer
*	if an error ocurred.
*	It stops parsing at null char and also at | or ; chars.
*	Empty spaces are ignored.
*/
int	arg_counter(t_shell *shell, const char *line, int pos)
{
	t_ac	a;

	a.j = pos;
	a.buff[1] = '\0';
	while (line[a.j] == ' ')
		a.j++;
	a.tmp = ft_strdup("");
	if (!a.tmp)
		return (miniperror(ERR_MEM));
	if (main_loop(shell, line, &a) != 1)
		return (-1 + (int)ft_free(a.tmp));
	free(a.tmp);
	if (line[a.j])
		a.j += 1;
	return (a.j);
}

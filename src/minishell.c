/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellaca-f <ericllaca@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 13:10:39 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 14:57:07 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "functions.h"
#include "utils.h"

/*
*	This functin parses and executes one command at a time with a loop,
*	the exit condition is a flag that activates when all the commands have
*	been parsed and executed, it also activates when forked process have
*	completed its purpose so they can end, and of course when an error
*	is returned.
*/
int	executer(t_shell *shell, char *line)
{
	void	*(*ms_cmd)(t_shell*);
	int		i;

	shell->pos = 0;
	i = 0;
	ms_cmd = NULL;
	while (!shell->forked)
	{
		if (!line[shell->pos])
			break ;
		shell->pos = parser(shell, &line, shell->pos);
		if (shell->pos == -1)
		{
			reset_argv(shell);
			break ;
		}
		ms_cmd = get_cmd(shell);
		piped_execution(shell, ms_cmd, line);
		reset_argv(shell);
		i++;
	}
	free(line);
	if (shell->forked)
		return (0);
	return (1);
}

/*
*	This is the wrapper function of the executer, it will be passed
*	to the line_edition functions.
*/
int	exe_hook(void *shell, char *line)
{
	return (executer((t_shell *)shell, line));
}

/*
*	The main function, it calls all the initializer functions
*	and starts the line edition loop, at end it frees the resources.
*	(Conviniently the shell struct is allocated on the stack to make
*	easier to free all the resources).
*/
int	main(int argc, char *argv[], const char **envp)
{
	t_shell	shell;
	t_cmd	cmd;

	if (init_shell(&shell, argc, argv, envp) < 0)
		return (1);
	shell.cmd = &cmd;
	cmd.argc = 0;
	cmd.argv = NULL;
	if (init_commands(&shell) < 0)
		return (1);
	line_edition_loop(&shell, shell.userpromt, exe_hook);
	env_free(&shell.env);
	return (0);
}

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
	shell->here_doc = 0;
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
*	Initializes the command array inside the shell struct.
*/
int	init_commands(t_shell *shell)
{
	shell->cmd->cmds[CMD_SIZE] = NULL;
	shell->cmd->reds = 0;
	shell->cmd->ms_cmds[CMD_SIZE] = NULL;
	shell->cmd->cmds[0] = "echo";
	shell->cmd->ms_cmds[0] = &ms_echo;
	shell->cmd->cmds[1] = "cd";
	shell->cmd->ms_cmds[1] = &ms_cd;
	shell->cmd->cmds[2] = "pwd";
	shell->cmd->ms_cmds[2] = &ms_pwd;
	shell->cmd->cmds[3] = "export";
	shell->cmd->ms_cmds[3] = &ms_export;
	shell->cmd->cmds[4] = "unset";
	shell->cmd->ms_cmds[4] = &ms_unset;
	shell->cmd->cmds[5] = "env";
	shell->cmd->ms_cmds[5] = &ms_env;
	shell->cmd->cmds[6] = "exit";
	shell->cmd->ms_cmds[6] = &ms_exit;
	shell->cmd->cmds[7] = NULL;
	shell->cmd->ms_cmds[7] = NULL;
	shell->cmd->exec = &ms_exec;
	return (0);
}

int	init_shell_vars(t_shell *shell)
{
	shell->ret = 0;
	shell->fd = 1;
	shell->userpromt = "minishell42>";
	shell->forked = 0;
	shell->isquoted = 0;
	shell->stdin_save = dup(STDIN_FILENO);
	shell->stdout_save = dup(STDOUT_FILENO);
	shell->stderr_save = dup(STDERR_FILENO);
	shell->pipe_write = STDOUT_FILENO;
	shell->prev_pipe_read = STDIN_FILENO;
	shell->i_hijos = 0;
	shell->args = NULL;
	shell->is_child = 0;
	return (1);
}

/*
*	Initializes the shell function given the initial args of our program
*/
int	init_shell(
	t_shell *shell, int argc, char *argv[], const char **envp)
{
	char	*tmp;

	g_envp = (char **)envp;
	if (argc > 1)
	{
		tmp = get_full_path(argv[1]);
		if (check_path_is_exec(tmp))
			return (miniperror(ERR_INVALID_FILE_OR_PATH));	
		shell->fd = open(argv[1], O_RDONLY);
		if (shell->fd < 0)
			return (-1);
		dup2(shell->fd, 0);
		close(shell->fd);
	}
	shell->env = env_init(envp);
	return (init_shell_vars(shell));
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

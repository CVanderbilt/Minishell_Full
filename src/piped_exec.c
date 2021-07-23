#include "minishell.h"

/*
*	If the command has pipes the process is forked and the pid returned,
*	also the read and write stored file descriptors are set to be the pipes.
*	If the command does not have pipes 0 is returned, no fork is made and the
*	write stored file descriptor is set to be stdout.
*/
int	pipes_checks(t_shell *shell, int *p, int has_pipes)
{
	if (has_pipes)
	{
		pipe(p);
		shell->pipe_read = p[0];
		shell->pipe_write = p[1];
		return (fork());
	}
	else
		shell->pipe_write = STDOUT_FILENO;
	return (0);
}

/*
*	Initial values are set on shell->pipe_write(stdout) and shell->prev_pipe_read(stdin)
*	and then redirections are applied on those variables, after all this the command is
*	executed and the stored file descriptors in shell->pipe_write... are closed.
*/
void	piped_parent_checks(t_shell *shell, void *(*ms_cmd)(t_shell*),
		int has_pipes)
{
	dup2(shell->pipe_write, STDOUT_FILENO);
	dup2(shell->prev_pipe_read, STDIN_FILENO);
	apply_redirections(shell, &(shell->args));
	if (has_pipes)
		close(shell->pipe_read);
	if (ms_cmd != 0)
		ms_cmd(shell);
	else
	{
		shell->ret = 127;
		miniperror(ERR_CMD_NOT_FOUND);
	}
	close(shell->prev_pipe_read);
	close(STDIN_FILENO);
	close(shell->pipe_write);
	close(STDOUT_FILENO);
}

/*
*	This functin makes some initial checks with a helper function
*	including the optional fork of the procces, the parent process
*	waits for its child to end its execution (waitpid), if its not
*	the main process the shell->forked flag is activated to make the
*	program exit.
*/
void	piped_parent(t_shell *shell, void *(*ms_cmd)(t_shell*),
		char *line, int has_pipes)
{
	int	status;

	piped_parent_checks(shell, ms_cmd, has_pipes);
	if (shell->pid)
	{
		waitpid(shell->pid, &status, 0);
		if (shell->is_child)
			shell->forked = 1;
		else
		{
			while (shell->cmd->reds == '|')
			{
				reset_argv(shell);
				shell->pos = parser(shell, &line, shell->pos);
			}
		}
	}
	else if (shell->is_child)
		shell->forked = 1;
}

/*
*	This function manages the execution of the command,
*	it calls the previous functions but in the end sorts
*	the process depending on if its the parent or the child,
*	the parent will execute the command and the child will continue
*	to execute a new command in parallel (only if pipes are being used).
*/
int	piped_execution(t_shell *shell, void *(*ms_cmd)(t_shell*), char *line)
{
	int	p[2];
	int	has_pipes;

	has_pipes = shell->cmd->reds == '|';
	shell->pid = pipes_checks(shell, p, has_pipes);
	if (!has_pipes || shell->pid)
		piped_parent(shell, ms_cmd, line, has_pipes);
	else
	{
		shell->is_child = 1;
		close(shell->pipe_write);
		shell->prev_pipe_read = shell->pipe_read;
	}
	return (0);
}

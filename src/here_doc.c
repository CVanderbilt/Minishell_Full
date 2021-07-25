#include "minishell.h"
#include "functions.h"
#include "utils.h"
#include "env_set.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <readline/readline.h>

static char	*here_doc_dups(t_shell *s)
{
	dup2(0, s->stdin_save);
	dup2(1, s->stdout_save);
	return (ft_strdup(""));
}

static int	here_doc_loop(char *ret, const char *word, int wfd)
{
	char	*line;
	char	*aux;

	while (1)
	{
		line = readline("> ");
		if (!line)
			return (1);
		aux = ft_append(ret, line);
		if (!aux)
			return (1 + (int)ft_free(line));
		if (!ft_strcmp(line, word))
		{
			ft_putstr_fd(wfd, ret);
			ft_dummy((int)ft_free(line) + (int)ft_free(ret));
			return (0);
		}
		free (ret);
		ret = ft_append(aux, "\n");
		free (aux);
		if (!ret)
			return (1 + (int)ft_free(line));
		free(line);
	}
	return (2);
}

static int	aux_here_doc(t_shell *s, const char *word, int wfd)
{
	char	*line;
	char	*ret;
	char	*aux;
	int		i;

	ret = here_doc_dups(s);
	if (!ret)
		return (0);
	i = here_doc_loop(ret, word, wfd);
	if (!i)
		return (0);
	if (i == 1)
		return (1);
	if (ret)
		free(ret);
	return (1);
}

/*
*	Reads line by line storing it, ends with eof or
*	when the keyword is readed.
*	not implemented - flag.
*/
int	red_here_doc(t_shell *s, const char *file, int fd)
{
	int	pid;
	int	status;
	int	pfd[2];

	pipe(pfd);
	pid = fork();
	if (pid)
	{
		close(pfd[1]);
		fd = 0;
		dup2(pfd[0], fd);
		waitpid(pid, &status, 0);
		return (1 + (int)ft_dummy(close(pfd[0])));
	}
	else
	{
		ft_dummy(dup2(s->stdin_save, 0) + dup2(s->stdout_save, 1)
			+ dup2(s->stderr_save, 2));
		aux_here_doc(s, file, pfd[1]);
		close(pfd[0]);
		close(pfd[1]);
		s->forked = 1;
		exit(0);
	}
	return (0);
}

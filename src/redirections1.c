#include "minishell.h"
#include "functions.h"
#include "utils.h"
#include "env_set.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <readline/readline.h>

/*
*	Returns the redirection type expresed by the string:
*	> redirect output,
*	>> redirect output append mode,
*	< redirect input,
*	<< here doc input redirection.
*/
t_redir	get_red_type(const char *str)
{
	if (str[0] == '>')
	{
		if (str[1] == '>' && !is_cmd_red(str[2]))
			return (RED_OUT_APP);
		else if (str[1] != '<')
			return (RED_OUT);
	}
	if (str[0] == '<')
	{
		if (str[1] == '<' && !is_cmd_red(str[2]))
			return (RED_HERE_DOC);
		else if (str[1] != '>')
			return (RED_IN);
	}
	return (RED_NONE);
}

/*
*	get_file returns a string containing the next word after a redirection.
*	[fd]>file -> returns file. (also > file, >file, etc).
*/
char	*get_file(const char *str)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && !is_cmd_red(str[i]))
		i++;
	ret = (char *)malloc (i + 1);
	if (!ret)
		return (0);
	i = -1;
	while (str[++i] && !is_cmd_red(str[i]))
		ret[i] = str[i];
	ret[i] = 0;
	return (ret);
}

typedef struct s_ee
{
	int		pid;
	int		status;
	int		p[2];
	char	c;
}	t_ee;

typedef struct s_rod
{
	int			fd2;
	struct stat	st;
}	t_rod;

char	*here_doc_dups(t_shell *s)
{
	dup2(0, s->stdin_save);
	dup2(1, s->stdout_save);
	return (ft_strdup(""));
}

int	here_doc_loop(char *ret, const char *word, int wfd)
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

/*
*	Reads line by line storing it, ends with eof or
*	when the keyword is readed.
*	not implemented - flag.
*
*	NEED TO CHECK: reading from file instead of console.
*/
int	aux_here_doc(t_shell *s, const char *word, int wfd)
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

int	red_out(t_rod *r, const char *file, t_redir type)
{
	if (type == RED_OUT)
		r->fd2 = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
	else
		r->fd2 = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (fstat(r->fd2, &r->st))
		return (-1);
	return (1);
}

int	red_open_dup_aux(t_shell *s, int fd, t_redir type)
{
	if (fd < 0 && (type == RED_HERE_DOC || type == RED_IN))
		fd = 0;
	else if (fd < 0)
		fd = 1;
	if (fd == s->stderr_save || fd == s->stdin_save || fd == s->stdout_save)
		return (0);
	return (1);
}

/*
*	red_open_dup depending on the redir type duplicates the fd corresponding
*	to the redirecting/ed file in the selected fd, in the < and << redirections
*	the fd is duplicated in stdin and in > and >> is duplicated in stdout.
*
*	Here_doc calls a helper function to take the input.
*/
int	red_open_dup(t_shell *s, int fd, const char *file, t_redir type)
{
	t_rod	r;

	if (!red_open_dup_aux(s, fd, type))
		return (0);
	if (type == RED_OUT || type == RED_OUT_APP)
	{
		if (red_out(&r, file, type) == -1)
			return (-1);
	}
	else if (type == RED_IN)
	{
		r.fd2 = open(file, O_RDONLY);
		if (fstat(r.fd2, &r.st))
			return (-1);
	}
	else if (type == RED_HERE_DOC)
		return (red_here_doc(s, file, fd));
	else
		return (-1);
	dup2(r.fd2, fd);
	if ((dup2(r.fd2, fd) || 1) && r.fd2 > 2)
		ft_close(r.fd2);
	return (1);
}

#include "minishell.h"
#include "utils.h"
#include "env_set.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "functions.h"
#include "ultra_utils.h"

typedef struct s_ee
{
	int		pid;
	int		status;
	int		p[2];
	char	c;
}	t_ee;

/*
*	This function will execute an external program, for that the process
*	is forked and the parent will wait for the child to exit, the child
*	will call the execve function on the given program.
*	When the parent ends waiting it reads from a pipe, if any info comes from
*	it that means the child failed, else the child exit correctly and
*	we set the last returned value to be the returned value of this program.
*/
int	exec_executer(t_shell *s, char *f, char **argv, char **envp)
{
	t_ee	e;

	pipe(e.p);
	e.pid = fork();
	if (!e.pid)
	{
		s->forked = 1;
		close(e.p[0]);
		if (execve(f, argv, envp) < 0)
		{
			write(e.p[1], "a", 1);
			close(e.p[1]);
			return (set_ret(s, miniperror(ERR_INVALID_FILE_OR_PATH)));
		}
		exit(0);
	}
	else
	{
		waitpid(e.pid, &e.status, (int)ft_dummy((close(e.p[1]))));
		if (read(e.p[0], &e.c, 1) == 0)
			return (set_ret(s, WEXITSTATUS(e.status)) * 0);
	}
	return (set_ret(s, -1) - 1);
}

/*
*	This function returns the next path in the path variable starting
*	in the given position, it returns a new string which have to be freed.
*/
char	*get_path_from_paths(const char *paths, unsigned int *pos)
{
	int				i;
	unsigned int	count;
	char			*ret;
	char			*aux;

	i = -1;
	count = 1;
	while (paths[++i])
	{
		if (count == *pos)
		{
			aux = ft_strcdup(paths + i, ':');
			if (!aux)
				return (0);
			ret = ft_strjoin(aux, "/", 'L');
			if (!ret)
				return (ft_free(ret));
			return (ret);
		}
		if (paths[i] == ':')
			count++;
	}
	*pos = 0;
	return (0);
}

/*
*	This program checks if the given path is an executable, it returns
*	1 if it is and 0 else.
*/
int	check_path_is_exec(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) == 0 && statbuf.st_mode & S_IXUSR)
		return (1);
	return (0);
}

/*
*	Returns a new string with the absolute path to the path provided, if the path
*	provided was an absolute path itself it copies it.
*/
char	*get_full_path(char *path)
{
	char	*ret;

	if (isAbsolute(path))
		return (ft_strdup(path));
	if (!ft_sstrjoin(getcwd(0, 0), "/", 'l', &ret))
		return (0);
	if (!ft_sstrjoin(ret, path, 'l', &ret))
		return (0);
	return (ret);
}

typedef struct s_sae
{
	char			*paths;
	char			*single_path;
	char			*new_path;
	unsigned int	pos;
}	t_sae;

/*
*	This function searchs in the PATH variable the command 'name', it
*	concatenates it at the end of each valid path (each path is separated by :)
*	and if any of them exists it is executed with the exec_executer, if not it
*	returns the error CMD_NOT_FOUND.
*/
static int	search_and_execute(t_shell *s, char *name, char **argv, char **envp)
{
	t_sae	t;

	t.paths = env_get(s->env, "PATH");
	if (!t.paths)
		return (set_ret(s, miniperror(ERR_MEM)));
	t.pos = 0;
	while (++t.pos)
	{
		t.single_path = get_path_from_paths(t.paths, &t.pos);
		if (t.pos && !t.single_path)
			return ((int)ft_free(t.paths) + set_ret(s, miniperror(ERR_MEM)));
		if (!t.pos)
			break ;
		t.new_path = ft_strjoin(t.single_path, name, 'L');
		if (!t.new_path)
			return ((int)ft_free(t.single_path) + (int)ft_free(t.paths)
				+ set_ret(s, miniperror(ERR_MEM)));
		if (check_path_is_exec(t.new_path))
		{
			argv[0] = t.new_path + (int)ft_free(t.paths) + (int)ft_free(argv[0]);
			return (exec_executer(s, argv[0], argv, envp));
		}
		free (t.new_path);
	}
	return ((int)ft_free(t.paths) + set_ret(s, miniperror(ERR_CMD_NOT_FOUND)));
}

/*
*	This function is called when the argument was not recognized as a builtin
*	function, if it is an absolute or relative path we execute it with the function
*	exec_executer, if it isnt a path we have to search it in the paths available
*	on the path variable with the function search_and_execute.
*/
int	ms_exec(t_shell *s)
{
	char	*filename;
	char	**envp;
	char	**argv;
	int		ret;

	filename = s->args->arg;
	argv = get_argv(s->args);
	envp = env_raw(s->env);
	if (!filename[0])
		return (1);
	if (ft_strfind(filename, '/') >= 0)
		ret = exec_executer(s, filename, argv, envp);
	else
		ret = search_and_execute(s, filename, argv, envp);
	free_argv(envp);
	free_argv(argv);
	return (ret);
}

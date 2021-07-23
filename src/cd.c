#include "minishell.h"
#include "utils.h"
#include "env_set.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "functions.h"

/*
*	All the ms_functions uses as arguments the parsed arguments that are stored
*	in the shell struct in s->args.
*/

/*
*	This function checks if the given string is an absolute path, returns 1 if it is
*	and 0 otherwise.
*/
int	isAbsolute(const char *path)
{
	if (!path)
		return (0);
	if (path[0] == '/')
		return (1);
	return (0);
}

/*
*	This function exports the variable OLDPWD with the value passed at old,
*	its used by the ms_cd function to set the oldpwd variable when changing directory.
*/
int	set_old_pwd(t_shell *s, const char *old)
{
	char	*path;
	int		ret;

	if (!env_add_safe(s->env, "OLDPWD", old))
		return (0);
	path = getcwd(NULL, 0);
	if (!path)
		return (0);
	ret = env_add_safe(s->env, "PWD", path);
	free (path);
	return (ret);
}

typedef struct s_cd
{
	char	*aux;
	int		check;
	char	**argv;
	char	*path;
	int		extra;
}	t_cd;

/*
*	This function makes some checks on the args passed to the ms_cd function,
*	if no arguments are passed then the HOME variable will be the argument, if
*	HOME was unset an error will be prompted and returned.
*/
int	ms_cd_aux(t_shell *s, t_cd *c)
{
	c->extra = 0;
	c->check = 0;
	c->path = getcwd(NULL, 0);
	c->argv = get_argv(s->args);
	if (!c->argv)
		return (0);
	if (!c->argv[1])
	{
		c->extra = 1;
		c->argv[1] = env_get(s->env, "HOME");
	}
	else if (!*c->argv[1])
	{
		c->extra = 1;
		free(c->argv[1]);
		c->argv[1] = env_get(s->env, "HOME");
	}
	if (!c->argv[1])
		miniperror(ERR_HOME_NOT_SET);
	return (1);
}

/*
*	If the aux function doesnt return an error this function will change the
*	current directory with the chdir function (if is absolute), if it is relative
*	a concatenation of the current directory with the argument passed is done before
*	the change of directory.
*	This function then calls the set_old_pwd function to set the OLDPWD variable to the
*	previous pwd.
*/
int	ms_cd(t_shell *s)
{
	t_cd	c;

	if (!ms_cd_aux(s, &c))
		return (0);
	if (isAbsolute(c.argv[1]))
		c.check = chdir(c.argv[1]);
	else if (c.argv[1])
	{
		c.aux = ft_strjoin(c.path, "/", ' ');
		c.aux = ft_strjoin(c.aux, c.argv[1], 'L');
		if (!c.aux)
			ft_putstr_fd(1, "Memory error");
		c.check = chdir(c.aux);
		free(c.aux);
	}
	if (c.check < 0)
		miniperror(ERR_INVALID_FILE_OR_PATH);
	if (!set_old_pwd(s, c.path))
		miniperror(ERR_MEM);
	if (c.extra)
		c.argv[1] = ft_free(c.argv[1]);
	return (set_ret(s, 1) + (int)ft_free(c.path) + (int)free_argv(c.argv));
}

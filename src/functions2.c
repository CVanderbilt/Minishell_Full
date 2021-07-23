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
*	This function exports a variable parsing the argument in the form
*	key=value, its stored in t_env struct in shell, if variable already exists
*	it is stored in there, the struct is a simple linked list with nodes containing
*	key, value and next node.
*	If no arguments are provided prints a sorted list of all variables.
*/
int	ms_export(t_shell *s)
{
	int		i;
	t_env	*aux;
	char	**argv;

	i = 0;
	argv = get_argv(s->args);
	if (!argv)
		return (set_ret(s, miniperror(ERR_MEM)));
	if (!argv[1])
		return ((int)free_argv(argv) + env_sorted_display_all(s->env));
	else
	{
		while (argv[++i])
		{
			if (argv[i][0] == '=')
			{
				ft_putstr_fd(2, "= : ");
				miniperror(ERR_WRONG_TOKEN);
			}
			else
			{
				aux = new_env(argv[i]);
				if (!aux)
					return ((int)free_argv(argv) + set_ret(s, miniperror(ERR_MEM)));
				env_add(s->env, aux);
			}
		}
	}
	free_argv(argv);
	return (set_ret(s, 1));
}

/*
*	This function searches in the list of variables the variable with the key
*	provided and deletes them from the struct of variables (shell->env).
*	n arguments are accepted, it can delete (unset) multiple keys with the same command.
*/
int	ms_unset(t_shell *s)
{
	int		i;
	t_env	*start;
	char	**argv;

	i = 0;
	argv = get_argv(s->args);
	if (!argv)
		return (set_ret(s, miniperror(ERR_MEM)));
	start = s->env;
	while (argv[++i])
		env_delete(&start, argv[i]);
	s->env = start;
	free_argv(argv);
	return (set_ret(s, 1));
}

/*
*	This function activates the flag that makes the program exit.
*/
int	ms_exit(t_shell *s)
{
	char	**argv;

	argv = get_argv(s->args);
	if (!argv)
		return (set_ret(s, miniperror(ERR_MEM)));
	else
	{
		if (arg_size(s->args) == 1)
			s->exit_code = 0;
		else
			s->exit_code = ft_atoi(argv[1]);
		s->forked = 1;
	}
	free_argv(argv);
	return (set_ret(s, 1));
}

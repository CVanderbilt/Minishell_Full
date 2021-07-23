/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellaca-f <ericllaca@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:34:52 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 15:23:11 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
*	This function just sets the last returned value of a program, the int passed is stored
*	int s->ret and thats all of it.
*	Depending on the ret value, the shell ret value is set to 0 (if ret is <= 0) or 1.
*/
int	set_ret(t_shell *s, int ret)
{
	if (ret <= 0)
		s->ret = 1;
	else
		s->ret = 0;
	return (ret);
}

/*
*	This funtion frees an array of strings terminated in null,
*	such as the arguments in any program.
*/
void	*free_argv(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
	return (0);
}

/*
*	This function prints to the standard output the
*	path to the current directory.
*/
int	ms_pwd(t_shell *s)
{
	char	*path;

	(void) s;
	path = getcwd(NULL, 0);
	if (!path)
		return (set_ret(s, miniperror(ERR_MEM)));
	ft_putstr_fd(1, path);
	write(1, "\n", 1);
	free (path);
	return (set_ret(s, 1));
}

/*
*	This function prints the arguments passed separated with spaces, if the
*	flag -n is present it wont end with a eol which by default it does.
*/
int	ms_echo(t_shell *s)
{
	int		i;
	char	**argv;
	int		eol;
	int		control;

	eol = 1;
	i = 1;
	argv = get_argv(s->args);
	if (!argv)
		return (set_ret(s, miniperror(ERR_MEM)));
	while (argv[i] && argv[i][0] == '-')
		if (ft_strlen(argv[i]) == 2 && argv[i++][1] == 'n')
			eol = 0;
	else
		break ;
	control = i;
	while (argv[i])
	{
		if (control != i)
			write(1, " ", 1);
		ft_putstr_fd(1, argv[i++]);
	}
	if (eol)
		ft_putstr_fd(1, "\n");
	return (set_ret(s, 1) + (int)free_argv(argv));
}

/*
*	This function prints in the stdout a list of all the variables that
*	have a value, the variables that dont (key="") are printed with export
*	without arguments.
*/
int	ms_env(t_shell *s)
{
	t_env	*tmp;

	tmp = s->env;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(1, tmp->key);
			ft_putstr_fd(1, "=");
			ft_putstr_fd(1, tmp->value);
			ft_putstr_fd(1, "\n");
		}
		tmp = tmp->next;
	}
	return (set_ret(s, 1));
}

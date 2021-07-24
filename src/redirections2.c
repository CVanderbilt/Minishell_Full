#include "minishell.h"
#include "utils.h"
#include "env_set.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "redirections.h"

typedef struct s_ar
{
	t_args	*tmp;
	t_args	*next;
	int		fd;
	int		i;
	t_redir	type;
	int		is_arg;
	char	*file;
	char	*word;
}	t_ar;

/*
*	Gets the redirection type parsing the argument, if it is a valid
*	valid type it goes on and make sure the named atribute of the redirection
*	is on the same argument, if not is on the next argument so we concatenate
*	this argument and the next (deleting the next).
*/
static int	apply_redirections_inner_loop_aux(t_ar *ar, t_args **list)
{
	ar->type = get_red_type(ar->tmp->arg + ar->i);
	if (!ar->type)
		return (-1);
	if (ar->type == RED_OUT_APP || ar->type == RED_HERE_DOC)
		ar->i += 2;
	else
		ar->i++;
	if (!ar->tmp->arg[ar->i])
	{
		if (!ar->next)
			return (-1);
		ar->tmp->arg = ft_strjoin(ar->tmp->arg, ar->next->arg, 'L');
		if (!ar->tmp->arg)
			return (-1);
		arg_delete(list, ar->next);
		ar->next = ar->tmp->next;
	}
	return (1);
}

/*
*	This function makes sure (with inner_loop_aux) that the redirection symbol
*	is followed by the named argument in the same string, the named argument
*	is retrieved with our get_file function and then uses it to open the
*	corresponding fd duplicate if it haves to (special case here_doc).
*/
static int	apply_redirections_inner_loop(t_shell *s, t_ar *ar, t_args **list)
{
	while (1)
	{
		if (apply_redirections_inner_loop_aux(ar, list) == -1)
			return (-1);
		ar->file = get_file(ar->tmp->arg + ar->i);
		if (!ar->file)
			return (-1);
		while (!is_cmd_red(ar->tmp->arg[ar->i]) && ar->tmp->arg[ar->i])
			ar->i++;
		red_open_dup(s, ar->fd, ar->file, ar->type);
		free(ar->file);
		if (!ar->tmp->arg[ar->i])
			break ;
		ar->fd = -1;
	}
	return (1);
}

/*
*	Checks wether or not an argument of the array is a redirection,
*	it is a redirection if it is a number before a valid redirection symbol,
*	a valid redirection symbol, or a string after a valid redirection symbol.
*	
*	The parts of a redirection can be splited in consecutive arguments or be
*	concatenated in the same argument
*	(2 > file == 2>file == 2 >file == 2> file).
*
*	In the end this function checks if the next argument in the array is a
*	redirection, if it starts with a number its parsed as the fd of the
*	redirection, independently of the number existing or not the next argument
*	must be a valid redirection symbol, if not it isnt a redirection.
*/
static void	apply_redirections_aux(t_ar *ar)
{
	ar->is_arg = 0;
	ar->i = 0;
	ar->fd = -1;
	if (ft_is_digit(ar->tmp->arg[ar->i]))
		ar->fd = ft_atoi(ar->tmp->arg);
	while (ft_is_digit(ar->tmp->arg[ar->i]) && ar->tmp->arg[ar->i])
		ar->i++;
	if (!is_cmd_red(ar->tmp->arg[ar->i]))
		ar->is_arg = 1;
	while (!is_cmd_red(ar->tmp->arg[ar->i]) && ar->tmp->arg[ar->i])
		ar->i++;
	if (ar->is_arg)
		ar->is_arg = ar->i;
	else
		ar->is_arg = 0;
}

/*
*	it parses the argument array, if redirections are applied the
*	corresponding arguments are removed from the array
*/
int	apply_redirections(t_shell *s, t_args **list)
{
	t_ar	ar;

	ar.word = 0;
	ar.tmp = *list;
	while (ar.tmp)
	{
		ar.next = ar.tmp->next;
		if (ar.tmp->is_red)
		{
			apply_redirections_aux(&ar);
			if (apply_redirections_inner_loop(s, &ar, list) == -1)
				return (-1);
			if (ar.is_arg)
			{
				ar.tmp->arg[ar.is_arg] = 0;
				ar.file = ft_strdup(ar.tmp->arg);
				free(ar.tmp->arg);
				ar.tmp->arg = ar.file;
			}
			else
				arg_delete(list, ar.tmp);
		}
		ar.tmp = ar.next;
	}
	return (1);
}

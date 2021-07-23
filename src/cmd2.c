#include "cmd.h"

/*
*	The functions in cmd are used to manage the args struct, which is a list
*	containing the arguments parsed.
*/

/*
*	Thes function frees all the resources used by the t_args list.
*/
void	arg_clean(t_args *list)
{
	void	*aux;

	while (list)
	{
		aux = list->next;
		free(list->arg);
		free(list);
		list = aux;
	}
}

/*
*	This function returns a new t_args list with the array of strings
*	passed.
*/
t_args	*newlist(const char *arg)
{
	t_args	*args;

	args = malloc(sizeof(t_args));
	if (!args)
		return (0);
	args->arg = ft_strdup(arg);
	args->arg_pos = 0;
	args->next = NULL;
	return (args);
}

/*
*	This function add a new node at the end of the list.
*/
void	arg_add(t_args **start, t_args *newlist)
{
	int		pos;
	t_args	*aux;

	if (!start || !newlist)
		return ;
	if (!(*start))
	{
		*start = newlist;
		return ;
	}
	pos = (*start)->arg_pos;
	aux = (*start);
	while (aux->next)
	{
		pos = aux->arg_pos;
		aux = aux->next;
	}
	aux->next = newlist;
	while (newlist)
	{
		newlist->arg_pos = ++pos;
		newlist = newlist->next;
	}
}

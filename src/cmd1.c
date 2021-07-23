/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellaca-f <ericllaca@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:40:59 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 15:54:17 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cmd.h"

/*
*	The functions in cmd are used to manage the args struct, which is a list
*	containing the arguments parsed.
*/

/*
*	This function returns the size of the t_args list.
*/
unsigned int	arg_size(t_args *start)
{
	int	count;

	count = 0;
	while (start)
	{
		count++;
		start = start->next;
	}
	return (count);
}

/*
*	This function creates and returns an array of strings(such us the one
*	received as argument in the main function) based on the argv list.
*/
char	**get_argv(t_args *start)
{
	char	**ret;
	int		size;
	int		i;

	i = 0;
	size = arg_size(start);
	ret = malloc (sizeof(char *) * (size + 1));
	if (!ret)
		return (0);
	ret[size] = NULL;
	while (start)
	{
		ret[i++] = ft_strdup(start->arg);
		if (!ret)
			return (0);
		start = start->next;
	}
	return (ret);
}

/*
*	This function deletes the node of the list with the given address.
*/
void	arg_delete(t_args **list, void *addr)
{
	int		i;
	t_args	*tmp;
	t_args	*prev;

	i = 0;
	prev = 0;
	tmp = *list;
	while (tmp)
	{
		if (tmp == addr)
		{
			free(tmp->arg);
			if (prev)
				prev->next = tmp->next;
			else
				*list = tmp->next;
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
		i++;
	}
}

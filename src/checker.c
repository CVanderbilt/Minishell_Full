/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellaca-f <ericllaca@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:44:57 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 14:22:00 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	This is a utility function which returns 1 if the char in the
*	given position of the string is in a certain special form such as
*	this char and the next form << or, they form >>,
*	or just the char is a certain char such as >, <, | and ;
*/
int	isspecialchar(const char *line, int j)
{
	if (line[j] == '<' && line[j + 1] == '<')
		return (2);
	else if (line[j] == '<')
		return (1);
	else if (line[j] == '>' && line[j + 1] == '>')
		return (2);
	else if (line[j] == '>')
		return (1);
	else if (line[j] == '|')
		return (1);
	else if (line[j] == ';')
		return (1);
	return (0);
}

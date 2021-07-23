/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellaca-f <ericllaca@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 14:53:16 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 14:53:23 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
*	When $ is found alone (ex. &/ or "some command$") the $ is expanded
*	to $, no parsing is needed, just copy of the char.
*/
int	get_var_no_key(char **dst, int *pos)
{
	char	*tmp;

	tmp = ft_strjoin(*dst, "$", 'L');
	if (!tmp)
		return (-2);
	*dst = tmp;
	*pos -= 1;
	return (-1);
}

/*
*	This function checks if the key to parse is $$ we expand it to $ (revisar esto),
*	or $? which we expand to the last output of a program.
*/
int	get_var_short_key(t_shell *s, int *pos, char **dst, const char *line)
{
	char	*tmp;

	if (line[*pos] == '$')
	{
		tmp = ft_strjoin(*dst, "$", 'L');
		if (!tmp)
			return (-2);
		*dst = tmp;
	}
	else if (line[*pos] == '?')
	{
		tmp = ft_itoa(s->ret);
		if (!tmp)
			return (-2);
		if (!ft_sstrjoin(*dst, tmp, 'b', dst))
			return (-2);
	}
	else
		get_var_no_key(dst, pos);
	return (-1);
}

/*
*	This function skips all the chars of the key, that is all the chars
*	different than a valid separator (' ', $, /, ...).
*	If the key length is 0 a special check has to be made.
*	(get_var_short_key).
*	It returns -1 if get_var_short_key is called and worked correctly,
*	if not but no errors it will return the position of the next char to parse,
*	and on error -2 is returned.
*/
int	get_var_first_check(t_shell *s, const char *line, char **dst, int *pos)
{
	int	i;
	int	aux;

	i = 0;
	aux = *pos + 1;
	while (line[++*pos] != ' ' && line[*pos] != '$' && line[*pos] != '/'
		&&line[*pos] != 92 && line[*pos] != '"' && line[*pos] != '\''
		&& line[*pos] != '?' && line[*pos] != '=' && line[*pos] != ':'
		&& line[*pos])
		i++;
	if (*pos == aux)
		return (get_var_short_key(s, pos, dst, line));
	return (i);
}

int	get_var_last(t_shell *s, char *key, char **dst)
{
	char	*tmp;

	if (!key)
		return (-1);
	tmp = env_get(s->env, key);
	free (key);
	if (!tmp)
		return (-1);
	if (!ft_sstrjoin(*dst, tmp, 'b', dst))
		return (-1);
	if (!dst)
		return (-1);
	return (1);
}

/*
*	This function is the first of a set of functions, its called
*	during the parsing when a $ is found in the line, and will expand the
*	variable onto the parsed string (dst).
*	It uses two helper functions that will do the work, this just returns
*	the error if something fails or the position where the parsing will
*	continue after this.
*/
int	get_var(t_shell *shell, const char *line, char **dst, int pos)
{
	int		i;
	int		aux;

	aux = pos + 1;
	i = get_var_first_check(shell, line, dst, &pos);
	if (i < -1)
		return (-1);
	if (i == -1)
		return (pos);
	if (get_var_last(shell, ft_strndup((line + aux), i), dst) < 0)
		return (-1);
	return (pos - 1);
}

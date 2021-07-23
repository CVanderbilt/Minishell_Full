#include <stdio.h>
#include <stdlib.h>
#include "env_set.h"
#include "utils.h"

/*
*	This function sorts the raw list of variables and then prints it
*	formatted as "declare -x key(=value)".
*/
int	env_sorted_display_all(t_env *start)
{
	char	**raw;
	int		i;
	int		aux;

	i = 0;
	raw = env_raw(start);
	if (!raw)
		return (0);
	while (raw[i])
		i++;
	sort_ptr_arr((void *)raw, i, ft_vstrcmp);
	i = -1;
	while (raw[++i])
	{
		ft_putstr("declare -x ");
		aux = ft_putcstr(raw[i], '=');
		if (raw[i][aux])
		{
			write(1, "=\"", 2);
			ft_putstr(raw[i] + aux + 1);
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		free(raw[i]);
	}
	free(raw);
	return (1);
}

/*
*	This function creates a new node with the key and value passed and
*	adds it to the list, this program manages al the necessary frees.
*/
int	env_add_safe(t_env *start, const char *key, const char *value)
{
	t_env	*next;

	if (!key || !start)
		return (0);
	next = new_env2(key, value);
	if (!next)
		return (0);
	env_add(start, next);
	return (1);
}

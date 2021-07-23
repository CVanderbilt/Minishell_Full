#include <stdio.h>
#include <stdlib.h>
#include "env_set.h"
#include "utils.h"

/*
*	This function returns the value corresponding the given key,
*	on error it returns null, on not found variable it returns
*	empty string "".
*/
char	*env_get(t_env *start, const char *key)
{
	t_env	*tmp;

	tmp = start;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (!tmp->value)
				return (ft_strdup(""));
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	return (ft_strdup(""));
}

/*
*	This function frees the list of variables and all its used resources.
*/
void	env_free(t_env **start)
{
	t_env	*next;
	t_env	*tmp;

	tmp = *start;
	while (tmp)
	{
		next = tmp->next;
		free (tmp->value);
		free (tmp->key);
		free (tmp);
		tmp = next;
	}
}

/*
*	This function returns the size of the list of variables.
*/
unsigned int	env_size(t_env *start)
{
	unsigned int	ret;

	ret = 0;
	while (start)
	{
		ret++;
		start = start->next;
	}
	return (ret);
}

/*
*	This function returns an array of strings formatting the list such as
*	passed to main, each string is formatted as "key=value".
*/
char	**env_raw(t_env *start)
{
	char	**ret;
	int		i;

	ret = (char **)malloc(sizeof(char *) * (1 + env_size(start)));
	if (!ret)
		return (0);
	i = 0;
	while (start)
	{
		if (start->value)
		{
			ret[i] = ft_append(start->key, "=");
			ret[i] = ft_strjoin(ret[i], start->value, 'L');
		}
		else
			ret[i] = ft_strdup(start->key);
		start = start->next;
		i++;
	}
	ret[i] = 0;
	return (ret);
}

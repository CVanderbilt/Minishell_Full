#include <stdio.h>
#include <stdlib.h>
#include "env_set.h"
#include "utils.h"

/*
*	This function creates a new node for the list with the string
*	formatted as "key=value".
*/
t_env	*new_env(const char *str)
{
	int		i;
	t_env	*ret;

	ret = (t_env *)malloc(sizeof(t_env));
	if (!ret)
		return (0);
	i = 0;
	ret->next = 0;
	ret->value = 0;
	while (str[i] && str[i] != '=')
		i++;
	ret->key = ft_strndup(str, i);
	if (!ret)
		ft_free(ret);
	if (str[i] == '=')
	{
		ret->value = ft_strdup(str + i + 1);
		if (!ret->value)
			return (ft_dummy((int)ft_free(ret->key) + (int)ft_free(ret)));
	}
	return (ret);
}

/*
*	This function returns a new node for the list with the key and the
*	value passed.
*/
t_env	*new_env2(const char *key, const char *value)
{
	t_env	*ret;
	char	*keycpy;
	char	*valuecpy;

	if (!key)
		return (0);
	ret = (t_env *)malloc(sizeof(t_env));
	if (!ret)
		return (0);
	keycpy = ft_strdup(key);
	if (!keycpy)
		return (ft_free(ret));
	valuecpy = 0;
	if (value)
	{
		valuecpy = ft_strdup(value);
		if (!value)
			return (ft_dummy((int)ft_free(keycpy) + (int)ft_free(ret)));
	}
	ret->key = keycpy;
	ret->value = valuecpy;
	ret->next = 0;
	return (ret);
}

/*
*	This function creates a new list of variables directly from
*	a array of strings such the one in the main function in which each
*	string is "key=value".
*/
t_env	*env_init(const char *str[])
{
	int		i;
	t_env	*aux;
	t_env	*ret;
	t_env	*prev;

	i = 0;
	ret = 0;
	prev = 0;
	while (str[i])
	{
		aux = new_env(str[i]);
		if (!aux)
			return (0);
		if (!ret)
			ret = aux;
		if (prev)
			prev->next = aux;
		prev = aux;
		i++;
	}
	return (ret);
}

/*
*	This function adds the passed node tho the list,
*	if the key already existed in the list the value is overwritten
*	and the passed node is freed.
*/
void	env_add(t_env *start, t_env *e)
{
	t_env	*tmp;

	tmp = start;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, e->key))
		{
			if (tmp->value && e->value)
				free (tmp->value);
			if (e->value)
				tmp->value = e->value;
			free(e->key);
			free (e);
			return ;
		}
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	tmp->next = e;
}

/*
*	This function deletes from the list of variables
*	the node containing the key passed.
*/
void	env_delete(t_env **start, const char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *start;
	prev = 0;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (!prev)
				*start = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

#include "utils.h"
#include "minishell.h"
#include "unistd.h"
#include <stdlib.h>

/*
*	Returns strlen of str until null, the next char is null or certain chars.
*/
int	ft_strlentil(char *str)
{
	int	i;

	i = 0;
	while ((str[i] != '\0' || str[i + 1] != '\0')
		&& str[i] != ' ' && !(isspecialchar(str, i)))
		i++;
	return (i);
}

/*
*	Compares two strings and returns 0 if equal or negative int if different.
*/
int	ft_vstrcmp(const void *s1, const void *s2)
{
	return (-1 * ft_strcmp((const char *)s1, (const char *)s2));
}

/*
*	Writes chars from str until null or certain char is find.
*/
int	ft_putcstr(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
	{
		write(1, str + i, 1);
		i++;
	}
	return (i);
}

/*
*	Duplicates string until null or certain char is find.
*/
char	*ft_strcdup(const char *str, char sep)
{
	int		i;
	char	*ret;

	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	ret = (char *)malloc (i + 1);
	if (!ret)
		return (0);
	i = -1;
	while (str[++i] && str[i] != ':')
		ret[i] = str[i];
	ret[i] = 0;
	return (ret);
}

/*
*	strjoin wraped, its the same function but if the f char provided is
*	in lowercase it ensures that the pointers are freed, even if the join
*	failed. (b, l r).
*	It will return 1 or 0 if an error ocurred, the joined string will be
*	stored in dst.
*/
int	ft_sstrjoin(char *l, char *r, char f, char **dst)
{
	char	*tmp;

	tmp = ft_strjoin(l, r, f);
	if (f == 'b' || f == 'l')
		free (l);
	if (f == 'b' || f == 'r')
		free (r);
	if (!dst)
		return (0);
	*dst = tmp;
	return (1);
}

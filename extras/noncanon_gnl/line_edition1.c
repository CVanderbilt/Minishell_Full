#include "line_edition.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

t_line	*line_error(t_line *l)
{
	l->err = 1;
	return (l);
}

int	line_advance_cursor(t_line *l)
{
	if (l->cursor < l->cursor_max)
	{
		l->cursor = l->cursor + 1;
		return (1);
	}
	return (0);
}

int	line_back_cursor(t_line *l)
{
	if (l->cursor > 0)
	{
		l->cursor = l->cursor - 1;
		return (1);
	}
	return (0);
}

t_line	*line_write(t_line *l, char *str)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;

	tmp = ft_strdup(l->str + l->cursor);
	if (!tmp)
		return (line_error(l));
	l->str[l->cursor] = 0;
	tmp2 = ft_strjoin(l->str, str, 'L');
	if (!tmp2)
	{
		free (tmp);
		return (line_error(l));
	}
	tmp3 = ft_strjoin(tmp2, tmp, 0);
	free (tmp);
	free(tmp2);
	if (!tmp3)
		return (line_error(l));
	l->str = tmp3;
	l->cursor_max = ft_strlen(l->str);
	return (l);
}

int	line_delete_cursor(t_line *l)
{
	int	i;

	i = l->cursor - 1;
	if (i < 0)
		return (0);
	l->cursor = i;
	while (l->str[i + 1])
	{
		l->str[i] = l->str[i + 1];
		i++;
	}
	l->str[i] = 0;
	l->cursor_max = ft_strlen(l->str);
	return (1);
}

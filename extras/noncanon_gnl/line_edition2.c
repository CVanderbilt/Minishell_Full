#include "line_edition.h"
#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

t_line	*line_reset(t_line *l)
{
	l->cursor = 0;
	l->cursor_max = 0;
	free (l->str);
	l->str = ft_strdup("");
	return (l);
}

t_line	new_line(void)
{
	t_line	l;

	l.cursor = 0;
	l.cursor_max = 0;
	l.str = ft_strdup("");
	if (!(l.str))
	{
		l.err = 1;
		return (l);
	}
	l.cursor_advance = &line_advance_cursor;
	l.cursor_back = &line_back_cursor;
	l.write = &line_write;
	l.cursor_delete = &line_delete_cursor;
	l.reset = &line_reset;
	l.err = 0;
	return (l);
}

t_history	new_history(void)
{
	t_history	h;

	h.i = 0;
	h.pos = 0;
	h.limit_up = 0;
	h.limit_down = 0;
	h.hist[0] = NULL;
	h.hist[1] = NULL;
	h.hist[2] = NULL;
	h.hist[3] = NULL;
	h.hist[4] = NULL;
	return (h);
}

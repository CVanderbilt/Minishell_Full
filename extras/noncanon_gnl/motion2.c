#include <stdio.h>
#include <termcap.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <errno.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <term.h>
#include "utils.h"
#include "kt_functions.h"
#include "line_edition.h"
#include "motion.h"

int	get_offset(t_key *k, int c)
{
	int	offset;

	offset = c - k->l.cursor % k->w.ws_col;
	if (offset < 0)
		offset = k->w.ws_col + offset;
	return (offset);
}

unsigned short	get_col(void)
{
	int	col;

	cursor_position(0, 0, &col);
	return ((unsigned)col);
}

unsigned short	get_row(void)
{
	int	row;

	cursor_position(0, &row, 0);
	return ((unsigned)row);
}

int	move_cursor_left(t_key *k)
{
	unsigned short	col;
	int				i;

	i = -1;
	col = get_col();
	if (!k->l.cursor_back(&k->l))
		return (0);
	if (col == 0)
	{
		tputs(tgetstr("up", 0), 1, ft_putchar0);
		while (++i < k->w.ws_col - 1)
			tputs(tgetstr("nd", 0), 1, ft_putchar0);
	}
	else
		tputs(tgetstr("le", 0), 1, ft_putchar0);
	return (1);
}

int	move_cursor_right(t_key *k)
{
	unsigned short	col;
	int				i;

	i = -1;
	col = get_col();
	if (!k->l.cursor_advance(&k->l))
		return (0);
	if (col == k->w.ws_col - 1)
	{
		tputs(tgetstr("do", 0), 1, ft_putchar0);
		tputs(tgetstr("cr", 0), 1, ft_putchar0);
	}
	else
		tputs(tgetstr("nd", 0), 1, ft_putchar0);
	return (1);
}

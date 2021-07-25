#include "kt_functions.h"
#include "utils.h"
#include "motion.h"
#include "ultra_utils.h"

void	line_deletion(t_key *k)
{
	int	eol1;
	int	offset;
	int	c;
	int	r;
	int	i;

	i = -1;
	if (!cursor_position(0, &r, &c))
		return ;
	offset = k->l.last_offset;
	if (k->l.last_key == KT_UNRECOGNIZED || k->l.last_key == KT_EOL)
		offset = get_offset(k, c);
	eol1 = k->w.ws_col - offset - 1;
	goto_cursor(k, 0);
	cursor_position(0, &r, &c);
	while (++i < (int)k->l.cursor_max)
		write(0, " ", 1);
	tputs(tgoto(tgetstr("cm", NULL), c, r), 0, ft_putchar0);
}

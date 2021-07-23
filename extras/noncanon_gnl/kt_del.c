#include "kt_functions.h"
#include "utils.h"
#include "motion.h"

int	kf_del(t_key *k)
{
	unsigned int	c;

	tputs(tgetstr("sc", NULL), 0, &ft_putchar0);
	c = k->l.cursor;
	if (!c)
		return (1);
	line_deletion(k);
	k->l.cursor = c;
	k->l.cursor_delete(&k->l);
	ft_putstr_fd(0, k->l.str);
	tputs(tgetstr("rc", NULL), 0, &ft_putchar0);
	k->l.cursor = c;
	move_cursor_left(k);
	return (1);
}

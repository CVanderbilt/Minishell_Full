#include "kt_functions.h"
#include "utils.h"
#include "motion.h"

int	kf_move(t_key *k)
{
	if (k->type == KT_LEFT)
		move_cursor_left(k);
	else if (k->type == KT_RIGHT)
		move_cursor_right(k);
	return (1);
}

int	kf_unrec(t_key *k)
{
	(void)k;
	return (1);
}

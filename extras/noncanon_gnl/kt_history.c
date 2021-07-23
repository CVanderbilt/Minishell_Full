#include "kt_functions.h"

int	kf_hist_print(t_key *k)
{
	int	c;

	line_deletion(k);
	ms_put_str(k, k->h.hist[k->h.pos]);
	k->l.reset(&k->l);
	k->l.write(&k->l, k->h.hist[k->h.pos]);
	c = k->l.cursor_advance(&k->l);
	while (c)
		c = k->l.cursor_advance(&k->l);
	return (1);
}

int	hs_move_cursor(t_key *k, t_motion m)
{
	if (m == MOTION_UP)
		k->h.pos--;
	else if (m == MOTION_DOWN)
		k->h.pos = (k->h.pos + 1) % 5;
	if (k->h.pos < 0)
		k->h.pos = 4;
	return (1);
}

static int	kf_up(t_key *k)
{
	if (!k->h.limit_up)
	{
		k->h.limit_down = 0;
		hs_move_cursor(k, MOTION_UP);
		if (k->h.pos == k->h.i && (hs_move_cursor(k, MOTION_DOWN)))
			return (++k->h.limit_up);
		if (k->h.hist[k->h.pos])
			kf_hist_print(k);
		else
			hs_move_cursor(k, MOTION_DOWN);
	}
	return (1);
}

static int	kf_down(t_key *k)
{
	if (!k->h.limit_down)
	{
		k->h.limit_up = 0;
		hs_move_cursor(k, MOTION_DOWN);
		if (k->h.pos == k->h.i)
			k->h.limit_down++;
		if (k->h.hist[k->h.pos])
			kf_hist_print(k);
	}
	return (1);
}

int	kf_updown(t_key *k)
{
	ft_save(k, k->l.str);
	if (k->type == KT_UP)
		return (kf_up(k));
	return (kf_down(k));
}

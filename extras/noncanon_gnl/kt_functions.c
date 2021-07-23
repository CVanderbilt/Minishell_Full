#include "kt_functions.h"
#include "utils.h"
#include "motion.h"

/*
*	This function is used to write strings on the minishell console,
*	it prevents the bug where the cursor wont wrap when writing until
*	the last column, this function checks if this bug is going to happen
*	and fixes it by moving the cursor to the correct position.
*/
void	ms_put_str(t_key *k, const char *str)
{
	unsigned int	col;
	unsigned int	len;

	col = get_col();
	len = ft_strlen(str);
	ft_putstr_fd(0, str);
	if (!((col + len) % k->w.ws_col))
	{
		tputs(tgetstr("do", 0), 1, ft_putchar0);
		tputs(tgetstr("cr", 0), 1, ft_putchar0);
	}
}

void	set_key_type(t_key *key)
{
	if (ISPRINTABLE(key->key[0]))
		key->type = KT_PRINTABLE;
	else if (key->key[0] == '\x1b')
	{
		if (key->key[1] == '[')
		{
			if (key->key[2] >= 'A' && key->key[2] <= 'D')
				key->type = KT_UP + (key->key[2] - 'A');
		}
	}
	else if (key->key[0] == 127)
		key->type = KT_DELETE;
	else if (key->key[0] == '\n')
		key->type = KT_EOL;
	else
		key->type = KT_UNRECOGNIZED;
}

int	get_key(t_key *key)
{
	read(0, key->key, 1);
	if (key->key[0] == 4 && !key->l.cursor_max)
		return (0);
	if (key->key[0] == '\x1b')
		read(0, key->key + 1, 3);
	set_key_type(key);
	return (1);
}

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

int	ft_save(t_key *key, const char *str)
{
	if (key->h.hist[key->h.pos])
		free(key->h.hist[key->h.pos]);
	key->h.hist[key->h.pos] = ft_strdup(str);
	return (1);
}

int	ft_manage_key(t_key *key)
{
	int	(*functptr[KT_FUNCNUM])(t_key*);

	functptr[0] = kf_unrec;
	functptr[1] = kf_print;
	functptr[2] = kf_move;
	functptr[3] = kf_updown;
	functptr[4] = kf_updown;
	functptr[5] = kf_move;
	functptr[6] = kf_move;
	functptr[7] = kf_del;
	functptr[8] = kf_eol;
	int ret = functptr[key->type](key);
	return (ret);
}

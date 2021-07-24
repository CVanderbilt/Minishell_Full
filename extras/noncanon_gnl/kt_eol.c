#include "kt_functions.h"
#include "utils.h"
#include "motion.h"

static int	ft_save_new(t_key *key, const char *str)
{
	key->h.pos = key->h.i;
	key->h.last = key->h.i;
	ft_save(key, str);
	key->h.i++;
	if (key->h.i > 4)
		key->h.i = 0;
	key->h.pos = key->h.i;
	key->h.limit_down = 1;
	key->h.limit_up = 0;
	return (1);
}

int	kf_eol(t_key *k)
{
	int		ret;
	char	*tmp;

	tmp = ft_strdup(k->l.str);
	move_cursors_to_end(k);
	new_line_reset(k);
	if (*tmp)
		ft_save_new(k, tmp);
	k->executing = 1;
	set_term_basic();
	ret = k->hook(k->data, tmp);
	set_term_specific();
	if (ret)
		write_prompt(k);
	k->executing = 1;
	return (ret);
}

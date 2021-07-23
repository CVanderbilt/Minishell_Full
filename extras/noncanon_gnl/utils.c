#include "utils.h"
#include <unistd.h>
#include <stdlib.h>

int	ft_putchar0(int c)
{
	return (write(0, &c, 1));
}

void	new_line_reset(t_key *k)
{
	write(2, "\n", 1);
	tputs(tgetstr("cr", 0), 1, &ft_putchar0);
	k->l.reset(&k->l);
}

void	write_prompt(t_key *k)
{
	write(2, k->prompt, k->prompt_len);
}

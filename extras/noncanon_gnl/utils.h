#ifndef UTILS_H
# define UTILS_H
# include "ultra_utils.h"
# include "sig_handler.h"
# include "kt_functions.h"
# include "line_edition.h"
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <term.h>

int		ft_putchar0(int c);
void	new_line_reset(t_key *k);
void	write_prompt(t_key *k);

#endif
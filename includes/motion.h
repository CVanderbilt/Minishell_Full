#ifndef MOTION_H
# define MOTION_H
# include "kt_functions.h"

int				get_offset(t_key *k, int c);
void			goto_cursor(t_key *k, unsigned int dst);
unsigned short	get_col(void);
unsigned short	get_row(void);
int				cursor_position(
					const int tty, int *const rowptr, int *const colptr);
int				move_cursor_left(t_key *k);
int				move_cursor_right(t_key *k);
int				move_cursors_to_back(t_key *k);
int				move_cursors_to_end(t_key *k);

#endif
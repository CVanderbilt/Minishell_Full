#ifndef LINE_EDITION_H
# define LINE_EDITION_H
# define PROMPT "prompt"
# define PROMPT_SIZE 6
# include "types.h"

typedef struct s_line
{
	unsigned int	cursor;
	unsigned int	cursor_max;
	char			*str;
	int				(*cursor_advance)(struct s_line*);
	int				(*cursor_back)(struct s_line*);
	int				(*cursor_delete)(struct s_line*);
	struct	s_line	*(*write)(struct s_line*, char *);
	struct	s_line	*(*reset)(struct s_line*);
	unsigned int	err;
	t_key_type		last_key;
	int				last_offset;
}	t_line;

typedef struct s_history
{
	char	*hist[5];
	int		i;
	int		pos;
	int		last;
	int		limit_up;
	int		limit_down;
}	t_history;

int			line_edition_loop(
				void *p, const char *str, int (*hook)(void *p, char *s));
/*
*	public
*/
void		set_term_basic(void);
int			set_term_specific(void);
int			line_advance_cursor(t_line *l);
int			line_back_cursor(t_line *l);
int			line_delete_cursor(t_line *l);
t_line		*line_reset(t_line *l);
t_line		*line_write(t_line *l, char *str);
t_line		new_line(void);
t_history	new_history(void);

#endif
#ifndef KT_FUNCTIONS_H
# define KT_FUNCTIONS_H
# define KT_FUNCNUM 9
# define ISPRINTABLE(c) (c > 31 && c < 127)
# include "line_edition.h"
# include <sys/ioctl.h>
# include <stdio.h>
# include <termcap.h>
# include <string.h>
# include <stdlib.h>
# include <termios.h>
# include <errno.h>
# include <termios.h>
# include <stdlib.h>
# include <unistd.h>
# include <term.h>
# include "ultra_utils.h"
# include "types.h"

typedef struct s_key
{
	int				chars;
	char			key[4];
	t_key_type		type;
	char			*line;
	t_line			l;
	t_history		h;
	int				(*hook)(void *data, char *line);
	void			*data;
	const char		*prompt;
	unsigned int	prompt_len;
	struct winsize	w;
	int				executing;
}	t_key;

t_key	*g_key;

/*
*	kf_functions.h
*/
void	ms_put_str(t_key *k, const char *str);
void	line_deletion(t_key *k);
//void	set_wdata(struct winsize (t_key *k));
void	set_wdata(t_key *k);
void	set_key_type(t_key *key);
int		get_key(t_key *key);
int		ft_manage_key(t_key *key);
int		ft_save(t_key *key, const char *str);
/*
*	actual kf_functions
*/
int		kf_unrec(t_key *k);
int		kf_print(t_key *k);
int		kf_move(t_key *k);
int		kf_updown(t_key *k);
int		kf_move(t_key *k);
int		kf_del(t_key *k);
int		kf_eol(t_key *k);
#endif
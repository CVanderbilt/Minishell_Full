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

char	**g_envp;
int		ft_strlentil(char *str);
char	*ft_strcdup(const char *str, char sep);
void	sort_ptr_arr(void **arr, unsigned int size,
			int (cmp)(const void *, const void*));
int		ft_vstrcmp(const void *s1, const void *s2);
int		ft_putcstr(const char *str, char c);

int		retfree1(int r, void *p);
int		retfree2(int r, void *p, void *p2);
int		retfree3(int r, void *p, void *p2, void *p3);
int		ft_sstrjoin(char *l, char *r, char f, char **dst);

#endif
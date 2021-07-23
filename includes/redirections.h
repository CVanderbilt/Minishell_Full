#ifndef REDIRECTIONS_H
# define REDIRECTIONS_H
# include "minishell.h"

t_redir	get_red_type(const char *str);
char	*get_file(const char *str);
int		red_open_dup(t_shell *s, int fd, const char *file, t_redir type);

#endif
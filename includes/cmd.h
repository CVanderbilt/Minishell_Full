/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ellaca-f <ericllaca@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/10 11:32:51 by ellaca-f          #+#    #+#             */
/*   Updated: 2021/05/07 15:26:52 by ellaca-f         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include "utils.h"

# define CMD_ARG 1
# define CMD_FILE 2

typedef enum e_redir
{
	RED_NONE,
	RED_OUT,
	RED_OUT_APP,
	RED_IN,
	RED_HERE_DOC,
	RED_ERR,
}			t_redir;

typedef struct s_redir_data
{
	int		fd;
	int		has_arg;
	t_redir	type;
	char	*arg;
	int		redirecting_to;
	int		error;
}				t_redir_data;

typedef struct s_args
{
	int			arg_pos;
	char		*arg;
	void		*next;
	int			is_red;
}				t_args;

t_args			*newlist(const char *arg);
void			arg_add(t_args **start, t_args *newlist);
unsigned int	arg_size(t_args *start);
char			**get_argv(t_args *start);
void			arg_clean(t_args *list);
void			arg_delete(t_args **list, void *addr);

#endif
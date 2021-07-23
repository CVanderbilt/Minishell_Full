#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include "utils.h"
#include <stdio.h>
#include "kt_functions.h"

typedef struct s_ruc
{
	char	*ret;
	char	*aux;
	char	buff[2];
	int		rb;
}	t_ruc;

char	*read_until_c(int fd, char e)
{
	t_ruc	r;

	r.buff[1] = 0;
	r.ret = ft_strdup("");
	while (1)
	{
		r.rb = read (fd, r.buff, 1);
		if (r.rb > 0)
		{
			r.aux = ft_strjoin(r.ret, r.buff, 0);
			free (r.ret);
			if (!r.aux)
				return (0);
			r.ret = r.aux;
			if (r.buff[0] == e)
				break ;
		}
		else if (!r.rb)
			break ;
		else
			return (ft_free(r.ret));
	}
	return (r.ret);
}

typedef struct s_cp
{
	char	*response;
	int		i;
	int		r;
	int		c;
}	t_cp;

void	cursor_position_loop(t_cp *c, int *const rowptr, int *const colptr)
{
	if (ft_strlen(c->response) < 6)
		return ;
	if (c->response[0] != 27 || c->response[1] != '[')
		return ;
	c->i = 2;
	c->r = ft_atoi(c->response + c->i);
	while (ft_is_digit(c->response[c->i]))
		c->i++;
	if (c->response[c->i] != ';')
		return ;
	c->c = ft_atoi(c->response + ++c->i);
	if (rowptr)
		*rowptr = c->r - 1;
	if (colptr)
		*colptr = c->c - 1;
}

int	cursor_position(
	const int tty, int *const rowptr, int *const colptr)
{
	t_cp	c;

	c.r = -1;
	c.c = -1;
	write(tty, "\033[6n", 4);
	c.response = read_until_c(tty, 'R');
	while (1)
	{
		cursor_position_loop(&c, rowptr, colptr);
		break ;
	}
	if (c.c < 0)
		return ((int)ft_free(c.response));
	return (1 + (int)ft_free(c.response));
}

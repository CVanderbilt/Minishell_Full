#include "utils.h"
#include "kt_functions.h"
#include "sig_handler.h"
#include <stdio.h>
#include <sys/ioctl.h>

void	handler(int signo)
{
	if (signo == SIGINT)
	{
		new_line_reset(g_key);
		write_prompt(g_key);
	}
	else if (signo == SIGWINCH)
		set_wdata(g_key);
}

int	sig_init(void)
{
	if (signal(SIGINT, handler) == SIG_ERR)
		return (0);
	if (signal(SIGWINCH, handler) == SIG_ERR)
		return (0);
	if (signal(SIGQUIT, handler) == SIG_ERR)
		return (0);
	return (1);
}

void	set_wdata(t_key *k)
{	
	ioctl(STDIN_FILENO, TIOCGWINSZ, &(k->w));
}

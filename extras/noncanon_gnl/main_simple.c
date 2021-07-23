#include <stdio.h>
#include <termcap.h>
#include <string.h>
#include <stdlib.h>
#include <termios.h>
#include <errno.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <term.h>
#include "utils.h"
#include "kt_functions.h"
#include "line_edition.h"
#include "motion.h"

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include "ultra_utils.h"

void	set_term_basic(void)
{
	struct termios	tattr;

	tcgetattr(STDIN_FILENO, &tattr);
	tattr.c_lflag |= (ECHO | ICANON);
	tattr.c_oflag |= (OPOST);
	tcsetattr(STDIN_FILENO, TCSADRAIN, &tattr);
}

int		set_term_specific(void)
{
	struct termios	tty;
	char			*termtype;

	if (tcgetattr(STDIN_FILENO, &tty) != 0)
		return (0);
		//printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
	tty.c_lflag &= ~ICANON;
	tty.c_lflag &= ~ECHO;
	tty.c_oflag &= ~OPOST;
	tty.c_cc[VMIN] = 1;
	tty.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSADRAIN, &tty) != 0)
		printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
	termtype = getenv ("TERM");
	if (termtype == 0)
		return (0);
		//write(1, "implementar que funcione con un gnl normal!!\n", 45);
	tgetent(NULL, termtype);
	return (1);
}

void	ft_putchar(char c)
{
	write(0, &c, 1);
}

int	line_edition_loop_end(t_key *key)
{
	int	i;

	i = -1;
	while (++i < 5)
		free (key->h.hist[i]);
	free (key->l.str);
	set_term_basic();
	return (0);
}

int	alt_loop(void *data, int (*hook)(void *, char *))
{
	char	*line;
	int		control;
	int		eof;

	control = 1;
	while (1)
	{
		eof = get_next_line(&line);
		if (eof < 0) // error
			break ;
		control = hook(data, line);
		if (control == 0 || eof == 0)
			return (1);
	}
	return (0);
}

int	line_edition_loop(
	void *data, const char *prompt, int (*hook)(void *, char *))
{
	t_key	key;

	if (!set_term_specific())
		return (alt_loop(data, hook));
	sig_init();
	set_wdata(&key);
	g_key = &key;
	key.h = new_history();
	key.l = new_line();
	key.data = data;
	key.prompt = prompt;
	key.prompt_len = ft_strlen(prompt);
	key.type = KT_UNRECOGNIZED;
	write(0, key.prompt, key.prompt_len);
	key.hook = hook;
	while (1)
	{
		key.l.last_key = key.type;
		key.type = KT_UNRECOGNIZED;
		if (!get_key(&key))
			break ;
		if (!ft_manage_key(&key))
			break ;
	}
	return (line_edition_loop_end(&key));
}

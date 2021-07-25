#include "minishell.h"
#include "utils.h"
#include "env_set.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/*
*	This function has 2 options:
*	1 will append the actual char to the parsed line.
*	2 will append the next char without treating it, and advance the index
*	so the parser never attepmts to treat it, this is the char overload \.
*/
int	if_helper(const char *line, t_ac *a, int option)
{
	if (option == 1)
	{
		a->tmp = ft_strjoin(a->tmp, a->buff, 'L');
		if (!a->tmp)
			return (miniperror(ERR_MEM));
		if (is_cmd_red(a->buff[0]))
			a->is_red = 1;
	}
	else if (option == 2)
	{
		a->buff[0] = line[++a->j];
		if (!a->buff[0])
			return ((int)ft_free(a->tmp) + miniperror(ERR_MULTILINE));
		a->tmp = ft_strjoin(a->tmp, a->buff, 'L');
		if (!a->tmp)
			return (miniperror(ERR_MEM));
	}
	return (1);
}

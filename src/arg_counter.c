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
static int	if_helper(const char *line, t_ac *a, int option)
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

/*
*	This function checks the actual char, if it is a quote the function isquoted
*	will be called to manage them, after it if a redirection was find 0 will be returned
*	and if an error ocurred we asume it was a multiline error.
*	If the actual char was $ an expansion of the variable has to be done, so the function get_var
*	is called.
*	If the actual char was \ it is managed (it could provoke a multiline error).
*	else the char is just added to the parsed line.
*/
static int	inner_loop_aux(t_shell *shell, const char *line, t_ac *a)
{
	if (line[a->j] == '"' || line[a->j] == '\'')
	{
		a->j = isquoted(shell, line, a->j, &a->tmp);
		if (a->j == -1)
			return ((int)ft_free(a->tmp) + miniperror(ERR_MULTILINE));
		if (is_cmd_red(line[a->j]))
			return (0);
	}
	else if (line[a->j] == '$')
	{
		a->j = get_var(shell, line, &a->tmp, a->j);
		if (!a->j)
			return ((int)ft_free(a->tmp) + miniperror(ERR_MEM));
	}
	else if (line[a->j] == 92)
	{
		if (if_helper(line, a, 2) == -1)
			return (-1);
	}
	else
		if (if_helper(line, a, 1) == -1)
			return (-1);
	return (1);
}

/*
*	This function checks char by char in a loop, firstly if the char is a cmd_sep the loop is breaked.
*	else the flag is activated (the next return will be treated as an argument if no errors were present).
*	On each char the function inner_loop_aux is called which on 0 breaks the loop and on -1
*	an error is raised, any other result is ignored.
*/
static int	inner_loop(t_shell *shell, const char *line, t_ac *a)
{
	int	aux;

	while (1)
	{
		if (is_cmd_sep(line[a->j]) || line[a->j] == ' ')
			break ;
		a->flag = 1;
		a->buff[0] = line[a->j];
		aux = inner_loop_aux(shell, line, a);
		if (aux == -1)
			return (-1);
		if (aux == 0)
			break ;
		a->j++;
	}
	return (1);
}

/*
*	This function checks if there is a char different than
*	null and ' ' in the string, is used to check if it could be
*	another arg in the line.
*/
static int	check_if_has_extra_arg(const char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i])
		return (1);
	return (0);
}

/*
*	this function checks the actual char in the line, if it is a command separator it
*	returns a 0 so the main loop will end, if not it continues and set the flag to 0
*	(by default it is not an argument).
*	If it didnt ended to this point all spaces are skipped except one, then the function
*	inner_loop is called (this function is expected to return -1, if not an error will be raised).
*/
static int	main_loop_aux(t_shell *shell, const char *line, t_ac *a)
{
	a->is_red = 0;
	if (is_cmd_sep(line[a->j]))
	{
		shell->cmd->reds = line[a->j];
		if (shell->cmd->reds != '|' || check_if_has_extra_arg(line + a->j + 1))
			return (0);
		miniperror(ERR_MULTILINE);
		return (-1);
	}
	a->flag = 0;
	if (line[a->j] == ' ')
		while (line[a->j + 1] == ' ')
			a->j++;
	if (inner_loop(shell, line, a) != 1)
		return (-1);
	return (1);
}

/*
*	This function is the core function of the parser, it will traverse the line
*	string char by char, the main_loop_aux function will check and make the necessary
*	changes that each char provokes and will return after a group of chars is parsed
*	forming an argument, if it returns 0 the program ended, if it returns -1
*	an error was raised and else the loop continues and does a check:
*	if the flag 'flag' is activated that means that the argument is an argument it is
*	added to the args list.
*/
int	main_loop(t_shell *shell, const char *line, t_ac *a)
{
	int	aux;

	while (1)
	{
		aux = main_loop_aux(shell, line, a);
		if (aux == -1)
			return (-1);
		if (aux == 0)
			break ;
		if (a->flag)
		{
			shell->cmd->argc++;
			a->args = newlist(a->tmp);
			if (!a->args)
				return ((int)ft_free(a->tmp) + miniperror(ERR_MEM));
			a->args->is_red = a->is_red;
			arg_add(&shell->args, a->args);
			free(a->tmp);
			a->tmp = ft_strdup("");
		}
		else if (!(isspecialchar(line, a->j)))
			a->j++;
	}
	return (1);
}

#include "minishell.h"

/*
*	Check if certain char is a valid command separator (|, ; or null).
*/
int				is_cmd_sep(char c)
{
	if (c == '|' || c == ';' || !c)
		return (1);
	return (0);
}

/*
*	Check if certain char is a valid redirection (> or <).
*/
int				is_cmd_red(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

/*
*	Check if a certain char is preserved (not overloaded) inside double quotes (\, $ or ").
*/
int				is_preserved(char c)
{
	if (c == 92 || c == '$' || c == '"')
		return (1);
	return (0);
}
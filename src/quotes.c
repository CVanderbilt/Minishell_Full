#include "minishell.h"

/*
*	If the quotes are uneven and the next char is null
*	an attempt of multiline quotes has been made,
*	this function checks that, may be redundant.
*/
int	isquoted_uneven_end(const char *line, int pos)
{
	if (line[pos])
		return (pos);
	return (-1);
}

/*
*	This function parses the quoted piece into the parsed line (dst),
*	certain chars are managed such as \(override next char is special)
*	and $(expand variable).
*	It returns (-1 on error, 0 if missing closing quotes and 1 on success).
*/
int	isquoted_loop(t_shell *shell, const char *line, int *pos, char **dst)
{
	char	flag;
	char	quote;
	char	buff[2];

	buff[1] = 0;
	quote = line[*pos - 1];
	while (line[*pos] != quote && line[*pos])
	{
		flag = 0;
		if (line[*pos] == 92 && quote == '"' && is_preserved(line[*pos + 1]))
			*pos += ++flag;
		buff[0] = line[*pos];
		if (line[*pos] == '$' && !flag && quote != '\'')
		{
			*pos = get_var(shell, line, dst, *pos);
			if (*pos < 0)
				return (-1);
		}
		else if (!ft_sstrjoin(*dst, buff, 'L', dst))
			return (-1);
		*pos += 1;
	}
	return (1);
}

/*
*	This function checks if the char in line[pos] is a quote, if it is
*	this function also manages them and makes the necesary change in the parsed
*	string (dst).
*/
int	isquoted(t_shell *shell, const char *line, int pos, char **dst)
{
	char	quote;

	quote = line[pos];
	if (quote == '"' || quote == '\'')
	{
		pos++;
		if (isquoted_loop(shell, line, &pos, dst) < 0)
			return (-1);
		return (isquoted_uneven_end(line, pos));
	}
	return (0);
}

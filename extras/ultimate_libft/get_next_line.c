#include "ultra_utils.h"

/*
*	Simple get next line function, stores next line in
*	argument line, returns -1 if error, 0 if eof reached
*	and else 1.
*/
int	get_next_line(char **line)
{
	int		rb;
	char	buff[2];
	char	*ret;

	ret = ft_strdup("");
	buff[1] = 0;
	rb = read(0, buff, 1);
	while (rb > 0)
	{
		if (*buff == '\n')
		{
			*line = ret;
			return (1);
		}
		ret = ft_strjoin(ret, buff, 'L');
		rb = read(0, buff, 1);
	}
	if (rb < 0)
		return (-1);
	*line = ret;
	return (0);
}
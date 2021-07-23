#include "ultra_utils.h"

int	ft_is_printable(char c)
{
	if (c > 31 && c < 127)
		return (1);
	return (0);
}

int	ft_is_digit(char c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

#include "ultra_utils.h"

void	ft_putstr(const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(1, str + i, 1);
}

void	ft_putstr_fd(int fd, const char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		write(fd, str + i, 1);
}

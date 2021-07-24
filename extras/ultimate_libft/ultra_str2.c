#include "ultra_utils.h"

void	ft_putnbr_fd(int fd, long long num)
{
	char	c;

	if (num < 0)
	{
		write(fd, "-", 1);
		num = -num;
	}
	if (num >= 10)
	{
		ft_putnbr_fd(fd, num / 10);
		num = num % 10;
	}
	if (num < 10)
	{
		c = num + 48;
		write(fd, &c, 1);
	}
}
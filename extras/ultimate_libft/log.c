#include "ultra_utils.h"
#include <sys/stat.h>
#include <fcntl.h>

int	ft_log(const char *str)
{
	int	fd;
	
	fd = open("ft_log.txt", O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (fd < 0)
		return (fd);
	ft_putstr_fd(fd, str);
	return (close(fd));
}

int ft_logn(const char *str)
{
	int	fd;
	
	fd = open("ft_log.txt", O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (fd < 0)
		return (fd);
	ft_putstr_fd(fd, str);
	write(fd, "\n", 1);
	return (close(fd));
}

int	ft_nlog(long long int num)
{
	int fd;

	fd = open("ft_log.txt", O_WRONLY | O_CREAT | O_APPEND, S_IRWXU);
	if (fd < 0)
		return (fd);
	ft_putnbr_fd(fd, num);
	return (close(fd));
}
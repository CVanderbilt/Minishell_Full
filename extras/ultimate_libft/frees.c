#include "ultra_utils.h"
#include <stdlib.h>

void	*ft_free(void *ptr)
{
	free (ptr);
	return (0);
}

void	*ft_dummy(int n)
{
	if (n)
		n++;
	return (0);
}

void	*ft_close(int fd)
{
	close (fd);
	return (0);
}

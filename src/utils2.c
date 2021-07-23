#include "utils.h"
#include "minishell.h"
#include "unistd.h"
#include <stdlib.h>

/*
*	This function sorts an array of pointers using the
*	function passed as argument to compare them.
*/
void	sort_ptr_arr(void **arr, unsigned int size,
		int (cmp)(const void *, const void*))
{
	unsigned int	i;
	void			*aux;
	int				changed;

	i = -1;
	changed = 0;
	if (size < 2)
		return ;
	while (++i || 1)
	{
		if (i >= size - 1)
		{
			if (!changed)
				return ;
			changed = 0;
			i = 0;
		}
		if (cmp(arr[i], arr[i + 1]) < 0)
		{
			aux = arr[i];
			arr[i] = arr[i + 1];
			arr[i + 1] = aux;
			changed = 1;
		}
	}
}

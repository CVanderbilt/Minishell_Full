#include "line_edition.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int hook(void* data, char*ln)
{
	char *tmp;
	int ret;

	ret = 1;
	tmp = (char*)data;
	write(1, "data:", 5);
	for (int i = 0; tmp[i]; i++)
		write(1, tmp + i, 1);
	write(1, "\nline:", 6);
	for (int i = 0; ln[i]; i++)
		write(1, ln + i, 1);
	write(1, "\n", 1);
	if (ln[0] == 'q')
		ret = 0;
	free (ln);
	return (ret);
}

int main(void)
{
	/*
	*	int line_edition_loop(void *data, const char *prompt, int (*hook)(void *, char *))
	*	void *data will be passed to hook
	*	prompt to be printed after each \n
	*	hook function
	*/
	const char* data = "data1234";
	line_edition_loop((void*)data, "prompt", hook);
}
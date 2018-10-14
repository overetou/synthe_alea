#include "utils.h"

void	exit_msg(const char *to_disp)
{
	printf("%s\n", to_disp);
	_Exit(0);
}

void		test_exit(void	*test_ptr, char *msg)
{
	if (!test_ptr)
		exit_msg(msg);
}

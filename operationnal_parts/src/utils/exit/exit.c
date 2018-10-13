#include "utils.h"

static void	exit(const char *to_disp)
{
	printf("%s\n", to_disp);
	_exit();
}

void		test_exit(void	*test_ptr, char *msg)
{
	if (!test_ptr)
		exit(msg);
}

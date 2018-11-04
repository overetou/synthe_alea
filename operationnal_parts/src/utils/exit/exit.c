#include "exit.h"
//Display a message passed as argument and exits.
void	exit_msg(const char *to_disp)
{
	printf("%s\n", to_disp);
	_Exit(0);
}

//test passed assesment. If true, nothing happens. If false, calls exit_msg with passed string.
void		test_exit(void*	test_ptr, char *msg)
{
	if (!test_ptr)
		exit_msg(msg);
}

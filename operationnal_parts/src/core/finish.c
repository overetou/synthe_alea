#include "core.h"

//Unallocate the vector list. No memory leaks possible, checked with valgrind.
void	finish(t_vector* spectrum)
{
	free_vector(spectrum);
}

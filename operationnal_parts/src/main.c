#include "core.h"

int	main(int argc, char **arg_str)
{
	t_vector*	spectrum;

	spectrum = initialize(argc, arg_str);
	do_operations(spectrum);
	finish(spectrum);
	return (0);
}

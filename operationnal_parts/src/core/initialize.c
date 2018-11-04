#include "utils.h"

//test if input = 1 arg, else exits. Use a func that allocates and get vectors from a well formated text file.
t_vector*	initialize(int argc, char **arg_str)
{
	t_vector*	spectrum;
	if (argc != 2)
		exit_msg("Wrong number of argument.\nusage : ./synthe file_to_extract");
	spectrum = get_vect_from_file(arg_str[1]);
	return (spectrum);
}

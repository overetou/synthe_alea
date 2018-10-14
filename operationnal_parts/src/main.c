#include "utils.h"

int	main(int argc, char **arg_str)
{
	t_vector*	spectrum;

	if (argc != 2)
	{
		printf("%s\n", "usage: ./synthe <file>");
		return (0);
	}
	spectrum = get_vect_from_file(arg_str[1]);
	//Do some stuff.
	printf("Septrum exists.\n");
	free_vector(spectrum);
	return (0);
}

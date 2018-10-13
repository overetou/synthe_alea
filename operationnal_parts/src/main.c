#include "utils.h"

int	main(int argc, char **arg_str)
{
	if (argc != 2)
	{
		printf("%s\n", "usage: ./synthe <file>")
		return (0);
	}
	get_vect(arg_str[1]);
	return (0);
}

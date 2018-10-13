#include "utils.h"

static FILE*	open_file(char *file_name)
{
	FILE *to_test_fd;


	to_test_fd = fopen(file_name);
	test_exit(to_test_fd, "Problem at file opening.")
	return (to_test_fd);
}

void	close_file(FILE* raw_file)
{
	fclose(raw_file);
}


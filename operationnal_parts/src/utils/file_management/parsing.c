#include "utils.h"

LI	get_file_length(FILE* raw_file)
{
	long int	size;

	fseek(raw_file, 0L, SEEK_END);
	size = (long int)ftell(raw_file);
	rewind(raw_file);
	return (size - 1);
}

char	get_char(FILE* raw_file)
{
	return ((char)fgetc(raw_file));
}

void	advance_and_check(FILE* raw_file, char to_match, int to_cross, LI* to_travel)
{
	if (to_cross > *to_travel)
		exit_msg("Separators are missing");
	*to_travel -= to_cross;
	while (to_cross)
	{
		if (get_char(raw_file) != to_match)
			exit_msg("Bad file format : unwelcome caractere spotted.");
		to_cross--;
	}
}

int	extract_int(FILE* raw_file, LI* to_travel, char separator)
{
	char	buff[INT_MAX_LENGTH];
	int	i = 0;
	int	extracted_int;
	
	buff[0] = get_char(raw_file);
	(*to_travel)--;
	printf("%c, to_travel = %ld, sep ='%c'\n", buff[0], *to_travel, separator == '\n' ? 'n' : separator);//test
	
	if (!is_digit(buff[0]) || !(*to_travel))
		exit_msg ("Bad file format : missing int.");
	
	
	
	
	while ((buff[++i] = get_char(raw_file)) != separator)
	{
		(*to_travel)--;
		printf("%c, to_travel = %ld\n", buff[i], *to_travel);//test
		if (!(*to_travel))
			exit_msg("no travel left.");
		else if(!is_digit(buff[i]))
			exit_msg("digit not working ?");
		else if (i > INT_MAX_LENGTH)
			exit_msg("Bad file format : int not well formed");
	}
	(*to_travel)--;



	extracted_int = str_to_int(buff);
	if ((i == INT_MAX_LENGTH && extracted_int < 0) || i == 0)
		exit_msg("Too big number for int in the file or no int");
	printf("%s\n", "Exiting extractor.");
	return (extracted_int);
}

FILE*	open_file(char *file_name)
{
	FILE *to_test_fd;


	to_test_fd = fopen(file_name, "r");
	if (!to_test_fd)
		test_exit(to_test_fd, "Problem at file opening.");
	return (to_test_fd);
}

void	close_file(FILE* raw_file)
{
	fclose(raw_file);
}

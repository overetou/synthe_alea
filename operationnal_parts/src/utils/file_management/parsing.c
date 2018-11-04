#include "utils.h"

//Takes a file as parameter. 1: puts the file cursor at the end of the file. 2: puts the number of chars measured into a long int variable.
//3: puts the file cursor at the beginning of the file (its original place). 4: checks that the file is not empty, otherwise exits.
//5: return the long int - 1 (because the last char is not a char but an end of file(EOF) signal taken by the system reading functions and we must not try to read that else format error).
LI	get_file_length(FILE* raw_file)
{
	long int	size;

	fseek(raw_file, 0L, SEEK_END);
	size = (long int)ftell(raw_file);
	rewind(raw_file);
	return (size - 1);
}

//reads a char from a file and return it. The cast is here because fgetc extracts ascii values as int and we want our char to be nively typed.
//Note that the file reading cursor progresses automatically when reading with this system calls. So no incrementation needed here.
char	get_char(FILE* raw_file)
{
	return ((char)fgetc(raw_file));
}

//This function is currently not used, but is allows the user to cross a serie of identical chars (here we call them 'separators').
//Parsing phylosophy : everything is ok as long as it is awaited.
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

//Extracts an int from a file. The 'separator' argument is the char that is supposed to appear after the int text in the file. If not -> error, exit.
//While parsing the int, makes sure that : a number is not to big, that chars supposed to be digits are so, that end of file is not reached when not expected and that the expected separator is there.
//This func is bulky and not easy to read, there is a fair room for improvement.
int	extract_int(FILE* raw_file, LI* to_travel, char separator)
{
	char	buff[INT_MAX_LENGTH];
	int	i = 0;
	int	extracted_int;
	
	buff[0] = get_char(raw_file);
	(*to_travel)--;
	if (!is_digit(buff[0]) || !(*to_travel))
		exit_msg ("Found something else than a digit when not supposed to, or further reading impossible when it should have been.");
	while ((buff[++i] = get_char(raw_file)) != separator)
	{
		(*to_travel)--;
		if (!(*to_travel))
			exit_msg("no file content left while expecting int");
		else if(!is_digit(buff[i]))
			exit_msg("Found something else than a digit when not supposed to.");
		else if (i > INT_MAX_LENGTH)
			exit_msg("One number is to big to fit in.");
	}
	(*to_travel)--;
	extracted_int = str_to_int(buff);
	if ((i == INT_MAX_LENGTH && extracted_int < 0))
		exit_msg("Too big number for int");
	return (extracted_int);
}

//opens a file with a filename, checks if everything went well and return the file reference if so. Else exit.
FILE*	open_file(char *file_name)
{
	FILE *to_test_fd;


	to_test_fd = fopen(file_name, "r");
	if (!to_test_fd)
		test_exit(to_test_fd, "Problem at file opening.");
	return (to_test_fd);
}

//Closes a file stream.
void	close_file(FILE* raw_file)
{
	fclose(raw_file);
}

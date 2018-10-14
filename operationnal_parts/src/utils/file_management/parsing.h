#ifndef	PARSING_H
#define PARSING_H

#define LI long int
#define INT_MAX_LENGTH 10

#include "../exit/exit.h"//exit_msg, test_exit
#include "../type_management/conversion/conversion.h"//str_to_int
#include "../type_management/type_questions/type_questions.h"//is_digit

FILE*	open_file(char *file_name);
void	close_file(FILE* raw_file);
int	extract_int(FILE* raw_file, LI* to_travel, char separator);
void	advance_and_check(FILE* raw_file, char to_match, int to_cross, LI* to_travel);
LI	get_file_length(FILE* raw_file);

#endif

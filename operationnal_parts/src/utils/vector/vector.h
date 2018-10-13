
#ifndef	VECTOR_H
#define VECTOR_H

#include "../src/file_management/parsing.h"//extract_word, advance_one

typedef struct	s_vector
{
	int			n1;
	int			n2;
	struct s_vector*	next;
}		t_vector;

void	get_vect_from_file(char *file_name);

#endif

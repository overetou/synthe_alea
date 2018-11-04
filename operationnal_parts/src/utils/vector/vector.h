#ifndef	VECTOR_H
#define VECTOR_H

#include <stdlib.h>
#include <stdio.h>

typedef struct	s_vector
{
	int			n1;
	int			n2;
	struct s_vector*	next;
}		t_vector;

#include "../file_management/parsing.h"//open_file, extract_int, advance_one, close_file

t_vector*	get_vect_from_file(char *file_name);
void		free_vector(t_vector* to_free);
void		display_vector(t_vector* vector);

#endif

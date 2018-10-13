#include "vector.h"

t_vector	new_vector()
{
	return ((t_vector*)malloc(sizeof(t_vector)));
}

void		extract_vect_data(FILE* raw_file, t_vector* vector_ptr)
{
	long int	file_size;
	long int	traveled_memory;

	while (traveled_memory != file_size)
	{
		vector_ptr = new_vector();
		vector->n1 = extract_int(raw_file, &traveled_memory);
		advance_and_check(raw_file, " ", 1, &traveled_memory);
		vector->n2 = extract_int(raw_file, &traveled_memory);
		vector_ptr = vector_ptr->next;
	}
}

t_vector*	get_vect_from_file(char *file_name)
{
	FILE*		raw_file;
	t_vector*	vector_list;

	raw_file = open_file(file_name);
	extract_content(raw_file, vector);
	close_file(raw_file);
	return (vector);
}

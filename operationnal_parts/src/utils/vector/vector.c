#include "utils.h"

void*		secure_malloc(int size)
{
	void*	fresh_memory;

	fresh_memory = malloc(size);
	if (!fresh_memory)
		exit_msg("Malloc failed.");
	return (fresh_memory);
}

t_vector*	new_vector()
{
	return ((t_vector*)secure_malloc(sizeof(t_vector)));
}

void		free_vector(t_vector* to_free)
{
	t_vector*	next_vect;

	printf("found next\n");
	next_vect = to_free->next;
	while (next_vect)
	{
		free(to_free);
		to_free = next_vect;
		next_vect = to_free->next;
	}
	free(to_free);
}

void		append_vector(t_vector* current_last_vector)
{
	current_last_vector->next = new_vector();
	current_last_vector = current_last_vector->next;
}

void		extract_vect_data(FILE* raw_file, t_vector** vect_list_start)
{
	long int	to_travel;
	t_vector*	allocater;

	to_travel = get_file_length(raw_file);
	*vect_list_start = new_vector();
	allocater = *vect_list_start;
	while (to_travel)
	{
		append_vector(allocater);
		allocater->n1 = extract_int(raw_file, &to_travel, ' ');
		allocater->n2 = extract_int(raw_file, &to_travel, '\n');
		allocater = allocater->next;
		printf("to travel = %ld\n", to_travel);
	}
	allocater->next = NULL;
	printf("I made it !!\n");
}

t_vector*	get_vect_from_file(char *file_name)
{
	FILE*		raw_file;
	t_vector*	vector_ptr;

	raw_file = open_file(file_name);
	extract_vect_data(raw_file, &vector_ptr);
	close_file(raw_file);
	return (vector_ptr);
}

#include "utils.h"

//Display passed vector into the terminal. The loop ends when vector pointer becomes NULL.
void	display_vector(t_vector* vector)
{
	while (vector)
	{
		printf("%d, %d\n", vector->n1, vector->n2);
		vector = vector->next;
	}
}

//allocates memory and check that no problem occured before returning the pointer. If so, exits.
void*		secure_malloc(int size)
{
	void*	fresh_memory;

	fresh_memory = malloc(size);
	if (!fresh_memory)
		exit_msg("Malloc failed.");
	return (fresh_memory);
}

//allocates memory for a single vector struct/link (not a list), and use a cast to convert the void* (=generic) pointer to a vector struct pointer.
t_vector*	new_vector()
{
	return ((t_vector*)secure_malloc(sizeof(t_vector)));
}

//takes a pointer on the last link of a vector struct list and makes his 'next' point on a newly allocated vector struct.
//Could be upgraded with additionnaly advancing the pointer on next (thus needing to pass a pointer on pointer in argument)
//but not sure about it truly be a good trade of compacity against liberty.
void		append_vector(t_vector* current_last_vector)
{
	current_last_vector->next = new_vector();
}

//pass through a vector struct list and free everything, stopping at NULL. If doubting understanding this, draw a 3 link list and apply the algorithm step by step.
//You'll soon get the logic.
void		free_vector(t_vector* to_free)
{
	t_vector*	next_vect;

	next_vect = to_free->next;
	while (next_vect)
	{
		free(to_free);
		to_free = next_vect;
		next_vect = to_free->next;
	}
	free(to_free);
}

//extract two ints and put them in the passed vector link. 'To_travel' is passed to manage file end related errors. Why symbols are passed in extract int is explained on top of this particular function
void		fill_vector_link(t_vector* v_link, FILE* raw_file, long int* to_travel)
{
	v_link->n1 = extract_int(raw_file, to_travel, ' ');
	v_link->n2 = extract_int(raw_file, to_travel, '\n');
}

//1: To avoid permanently checking if the file is ending, we measure it once for all, limiting system calls (our worst foe in term of speed). Function using 'to_travel' will update it as they progress in the file, so we pass the adress of the int for each changes to be effective in this function scope.
//2: we assign fresh memory to a vector pointer, wich will be returned as the first vector of the list.
//3: In the loop, the allocater variable will be used to allocate and fill every needed link and their content.This loop is 'next based', meaning we will need to manualy fill the first link before launching the loop.
//Finally, when there is nothing left to extract and no error happened, we end our list with a NULL (in the 'next' of the last link) and return the first link of the list. 
t_vector*	extract_vect_data(FILE* raw_file)
{
	long int	to_travel;
	t_vector*	vector_list_first_link;
	t_vector*	allocater;

	to_travel = get_file_length(raw_file);
	vector_list_first_link = new_vector();
	allocater = vector_list_first_link;
	fill_vector_link(allocater, raw_file, &to_travel);
	while (to_travel)
	{
		append_vector(allocater);
		allocater = allocater->next;
		fill_vector_link(allocater, raw_file, &to_travel);
	}
	allocater->next = NULL;
	return(vector_list_first_link);
}

//1: makes sure that the argument is a valid file_name, opens the corresponding file stream and puts the file stream reference into raw_file.
//2: nicely extract a vector list from the file stream. 3 : closes the file stream and returns the vector list.
t_vector*	get_vect_from_file(char *file_name)
{
	FILE*		raw_file;
	t_vector*	vector_ptr;

	raw_file = open_file(file_name);
	vector_ptr = extract_vect_data(raw_file);
	close_file(raw_file);
	return (vector_ptr);
}

#include <libsynthalea.h>
#include <stdlib.h>

void alloc_mat(unsigned dim1, unsigned dim2, t_mat *mat)
{
	t_comp **m = malloc(dim1 * sizeof(*m));
	for (unsigned i = 0; i < dim1; i++)
	{
		*m = malloc(dim2 * sizeof(t_comp));
	}
	if (mat != NULL)
	{
		desalloc_matAF(mat);
	}
	mat->vecs = m;
	mat->dim1 = dim1;
	mat->dim2 = dim2;
}
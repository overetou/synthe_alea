#include <libsynthalea.h>
#include <stdlib.h>

void alloc_matAF(unsigned dim1, unsigned dim2, struct matAF *mat)
{
	struct compAF **m = malloc(dim1 * sizeof(*m));
	for (unsigned i = 0; i < dim1; i++)
	{
		*m = malloc(dim2 * sizeof(struct compAF));
	}
	if (mat != NULL)
	{
		desalloc_matAF(mat);
	}
	mat->comps = m;
	mat->dim1 = dim1;
	mat->dim2 = dim2;
}
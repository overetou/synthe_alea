#include <libsynthalea.h>

void desalloc_matAF(struct matAF *mat)
{
	for (unsigned i = 0; i < sizeof(mat) / sizeof(*mat); i++)
	{
		free(mat[i]);
	}
	free(*mat);
	mat->dim1 = 0;
	mat->dim2 = 0;
}
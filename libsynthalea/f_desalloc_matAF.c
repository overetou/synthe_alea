#include <libsynthalea.h>

void desalloc_matAF(matAF *mat)
{
	for (unsigned i = 0; i < sizeof(*mat); i++)
	{
		free(*mat[i]);
	}
	free(*mat);
}
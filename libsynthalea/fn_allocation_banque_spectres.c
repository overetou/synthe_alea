#include <libsynthalea.h>

void						allocation_banque_spectres(struct banque_spectres *bk_sp)
{
	if (bk_sp->allocation)
	{
		desallocation_banque_spectre(bk_sp);
	}
	bk_sp->collection_spectres = malloc(bk_sp->nombre_spectres * sizeof(struct spectre_analyse));
	bk_sp->allocation = true;
}
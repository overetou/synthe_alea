#include <libsynthalea.h>

void						allocation_spectre(struct spectre *sp)
{
	if (sp->allocation)
	{
		desallocation_spectre(sp);
	}
	sp->partiels_amplitudes = malloc(sp->nombre_partiels * sizeof(double));
	sp->partiels_frequences = malloc(sp->nombre_partiels * sizeof(double));
	sp->allocation = true;
}
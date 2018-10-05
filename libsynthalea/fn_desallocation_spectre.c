#include <libsynthalea.h>

void						desallocation_spectre(struct spectre *sp)
{
	if (sp->allocation)
	{
		free(sp->partiels_amplitudes);
		free(sp->partiels_frequences);
		sp->allocation = false;
	}
}
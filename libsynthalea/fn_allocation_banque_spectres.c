#include <libsynthalea.h>

void allocation_banque_spectres(struct banque_spectres *bk_sp)
{
	if (bk_sp->allocation)
	{
		desallocation_banque_spectre(bk_sp);
	}
	bk_sp->spectres_partiels_amplitudes = malloc(bk_sp->nombre_spectres * sizeof(&bk_sp->spectres_partiels_amplitudes));
	for (unsigned i = 0; i < bk_sp->nombre_spectres; i++) bk_sp->spectres_partiels_amplitudes[i] = malloc(sizeof(bk_sp->spectres_partiels_amplitudes) * bk_sp->nombre_partiels);
	bk_sp->spectres_partiels_frequences = malloc(bk_sp->nombre_spectres * sizeof(&bk_sp->spectres_partiels_frequences));
	for (unsigned i = 0; i < bk_sp->nombre_spectres; i++) bk_sp->spectres_partiels_frequences[i] = malloc(sizeof(bk_sp->spectres_partiels_frequences) * bk_sp->nombre_partiels);
	bk_sp->allocation = true;
}
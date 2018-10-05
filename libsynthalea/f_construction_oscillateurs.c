#include <libsynthalea.h>

void construction_oscillateurs(
	const double		*idx_temps, 
	const double		*evo_puissance, 
	const double		*evo_dispersion, 
	unsigned			nb_osc, 
	struct matAF		*bk_sp,
	struct matAF		*bk_osc)
{
	unsigned nb_instants = sizeof(*idx_temps) / sizeof(double);
	alloc_matAF(nb_osc, nb_instants, bk_osc);


	unsigned nb_partiels_max;
	struct matAF *bk_sp_selec;
	alloc_matAF(nb_instants, nb_partiels_max, bk_sp_selec);
}
#include <libsynthalea.h>

void						allocation_oscillateur(struct oscillateur *osc)
{
	if (osc->allocation)
	{
		desallocation_oscillateur(osc);
	}
	osc->coefficients_amplitudes = malloc(osc->nombre_coefficients * sizeof(double));
	osc->coefficients_frequences = malloc(osc->nombre_coefficients * sizeof(double));
	osc->allocation = true;
}
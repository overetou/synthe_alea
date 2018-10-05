#include <libsynthalea.h>

double synthese(
	unsigned		i_echantillon,
	double			frequence,
	double			velocite,
	unsigned		frequence_echantillonnage,
	matAF			*bk_osc)
{
	double 			t;							// f de indice_echantillon, frequence_echantillonnage
	double 			facteur_puissance;
	double 			osc_amplitude;
	double 			osc_frequence;

	double 			somme_osc = 0;
	for (unsigned i_osc = 0; i_osc < sizeof(*bk_osc); i_osc++)
	{
		osc_ampl = 0;
		osc_freq = 0;
		for (unsigned i_coef = 0; i_coef < sizeof(*bk_osc[i_osc]; i_coef++)
		{
			facteur_puissance = pow(t, i_coef);
			osc_ampl += *bk_osc[i_osc][i_coef][_ampl] * velocite * facteur_puissance;
			osc_freq += *bk_osc[i_osc][i_coef][_freq] * frequence * facteur_puissance;
		}
		somme_osc += osc_ampl * sin(2 * 3.14 * osc_freq * t);
	}
	return somme_osc;
}
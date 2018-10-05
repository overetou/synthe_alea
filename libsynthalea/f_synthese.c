#include <libsynthalea.h>

double synthese(
	unsigned		i_echantillon,
	double			frequence,
	double			velocite,
	unsigned		frequence_echantillonnage,
	t_matAF			*bk_osc)
{
	double 			t = i_echantillon / frequence_echantillonnage;
	double 			somme_osc = 0;
	for (unsigned i_osc = 0; i_osc < bk_osc->dim1; i_osc++)
	{
		double osc_ampl = 0;
		double osc_freq = 0;
		for (unsigned i_coef = 0; i_coef < bk_osc->dim2; i_coef++)
		{			
			double facteur_puissance = pow(t, i_coef);
			osc_ampl += bk_osc->vec[i_osc].comps[i_coef].ampl * velocite * facteur_puissance;
			osc_freq += bk_osc->vec[i_osc].comps[i_coef].freq * frequence * facteur_puissance;
		}
		somme_osc += osc_ampl * sin(2 * 3.14 * osc_freq * t);
	}
	return somme_osc;
}
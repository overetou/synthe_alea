#include <libsynthalea.h>

#define PI 3.14159265358979323846

double synthese(
	unsigned		i_echantillon,
	double			frequence,
	double			velocite,
	unsigned		frequence_echantillonnage,
	t_mat			*bk_osc)
{
	double 			t;
	double			osc_ampl;
	double			osc_freq;
	double			facteur_puissance;
	double 			somme_osc;
	unsigned		i_osc;
	unsigned		i_coef;

	t = i_echantillon / frequence_echantillonnage;
	somme_osc = 0;
	for (i_osc = 0; i_osc < bk_osc->dim1; i_osc++)
	{
		osc_ampl = 0;
		osc_freq = 0;
		for (i_coef = 0; i_coef < bk_osc->dim2; i_coef++)
		{			
			facteur_puissance = pow(t, i_coef);
			t_compAF composante = (*bk_osc).vecs[i_osc].comps[i_coef].compAF;
			osc_ampl += composante.ampl * velocite * facteur_puissance;
			osc_freq += composante.freq * frequence * facteur_puissance;
		}
		somme_osc += osc_ampl * sin(2 * PI * osc_freq * t);
	}
	return somme_osc;
}
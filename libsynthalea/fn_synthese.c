#include <libsynthalea.h>

#include <math.h>

double				synthese(
						unsigned idx_echantillon,
						double frequence,
						double velocite,
						struct synthetiseur *synth)
{	
	double 			indice_temporel; // f de indice_echantillon, frequence_echantillonnage

	double 			indice_puissance;
	double 			oscillateur_amplitude;
	double 			oscillateur_frequence;

	double 			somme_oscillateurs = 0;
	for (unsigned i_oscillateur = 0; i_oscillateur < synth->oscillateurs->nombre_oscillateurs; i_oscillateur++)
	{
		oscillateur_amplitude = 0;
		oscillateur_frequence = 0;
		for (unsigned i_coefficient = 0; i_coefficient < synth->oscillateurs->collection_oscillateurs[i_oscillateur].nombre_coefficients; i_coefficient++)
		{
			indice_puissance = pow(indice_temporel, i_coefficient);
			oscillateur_amplitude += synth->oscillateurs->collection_oscillateurs[i_oscillateur].coefficients_amplitudes[i_coefficient] * velocite * indice_puissance;
			oscillateur_frequence += synth->oscillateurs->collection_oscillateurs[i_oscillateur].coefficients_frequences[i_coefficient] * frequence * indice_puissance;
		}
		somme_oscillateurs += oscillateur_amplitude * sin(2 * 3.14 * oscillateur_frequence * indice_temporel);
	}

	if (abs(somme_oscillateurs) > 1) synth->gain = 1 / abs(somme_oscillateurs);
	return somme_oscillateurs * synth->gain;
}
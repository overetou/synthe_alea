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
	
	t_matAF *matVandermonde, *matL, *matU;
	t_vecAF *osc;
	double somme = 0;

	unsigned nb_partiels; // > nb_osc
	struct matAF *bk_sp_selec;



	////////////////////////////////////////////////////////	Partie aleatoire : trouver le bon spectre pour chaque instant

	// Matrice des spectres selectionnes et ordonnes par ordre chronologique
	alloc_matAF(nb_instants, nb_partiels, bk_sp_selec);








	////////////////////////////////////////////////////////	Suivi des voix a travers les spectres

	// Matrice des oscillateurs
	alloc_matAF(nb_osc, nb_instants, bk_osc);











	/////////////////////////////////////////////////////////	Interpolation

	// Construction de la matrice de Vandermonde avec les idx_temps
	alloc_matAF(nb_instants, nb_instants, matVandermonde);
	for (unsigned i = 0; i < nb_instants; i++)
	{
		for (unsigned j = 0; j < nb_instants, j++)
		{
			// La matrice de Vandermonde est identique pour les amplitudes et les fréquences
			(*matVandermonde).vecs[i].comps[j].ampl = pow(idx_temps[i], j);
		}
	}

	// Decomposition V = L * U
	for (unsigned j = 0; j < nb_instants; j++)
	{
		(*matL).vecs[j].comps[j].ampl = 1;
		for (unsigned i = 0; i < j; i++)
		{
			somme = 0;
			for (unsigned k = 0; k < j - 1; k++)
			{
				somme = somme + (*matL).vecs[i].comps[k].ampl * (*matU).vecs[k].comps[j].ampl;
			}
			(*matU).vecs[k].comps[j].ampl = (*matVandermonde).vecs[i].comps[j].ampl - somme;
		}
		for (unsigned i = j; i < nb_instants; i++)
		{
			somme = 0;
			for (unsigned k = 0; k < i - 1; k++)
			{
				somme = somme + (*matL).vecs[i].comps[k].ampl * (*matU).vecs[k].comps[j].ampl;
			}
			(*matL).vecs[k].comps[j].ampl = ((*matVandermonde).vecs[i].comps[j].ampl - somme) / (*matU).vecs[j].comps[j];
		}
	}

	// Resolution pour chaque oscillateur

	for (unsigned i_osc = 0; i_osc < nb_osc; i_osc++)
	{
		// s_vecAF currentVec = vecteur ayant pour composantes les i_osc èmes composantes de chaque spectre

		// Resolution par descente de L * y = currentVec

		// Resolution par remontee de U * x = y

		// Ajouter x dans bk_osc
	}
}
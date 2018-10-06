#include <libsynthalea.h>

void construction_oscillateurs(
	const double		*idx_temps, 
	const double		*evo_puissance, 
	const double		*evo_dispersion, 
	unsigned			nb_osc, 
	t_matAF				*bk_sp,
	t_matAF				*bk_osc)
{
	unsigned nb_instants = sizeof(*idx_temps) / sizeof(double);
	
	

	unsigned nb_partiels; // > nb_osc
	struct matAF *bk_sp_selec;



	////////////////////////////////////////////////////////	Partie aleatoire : trouver le bon spectre pour chaque instant

	// Matrice des spectres selectionnes et ordonnes par ordre chronologique
	alloc_matAF(nb_instants, nb_partiels, bk_sp_selec);








	////////////////////////////////////////////////////////	Suivi des voix a travers les spectres

	// Matrice des oscillateurs
	alloc_matAF(nb_osc, nb_instants, bk_osc);











	/////////////////////////////////////////////////////////	Interpolation
	t_matAF 				*matVandermonde, 
							*matL, 
							*matU;

	t_vecAF 				*x, 
							*y;

	double 					somme;
	t_compAF 				sommeAF;

	// Transposition de bk_sp_selec
	t_matAF					*matB; // = transpose(bk_sp_selec)

	// Construction de la matrice de Vandermonde avec les idx_temps
	alloc_matAF(nb_instants, nb_instants, matVandermonde);
	for (unsigned i = 0; i < nb_instants; i++)
	{
		for (unsigned j = 0; j < nb_instants; j++)
		{
			// La matrice de Vandermonde est identique pour les amplitudes et les fr�quences
			(*matVandermonde).vecs[i].comps[j].ampl = pow(idx_temps[i], j);
		}
	}

	// Decomposition V = L * U
	for (unsigned j = 0; j < nb_instants; j++)
	{
		(*matL).vecs[j].comps[j].ampl = 1;
		for (unsigned i = 0; i < j + 1; i++)
		{
			somme = 0;
			for (unsigned k = 0; k < i - 1; k++)
			{
				somme = somme + (*matL).vecs[i].comps[k].ampl * (*matU).vecs[k].comps[j].ampl;
			}
			(*matU).vecs[i].comps[j].ampl = (*matVandermonde).vecs[i].comps[j].ampl - somme;
		}
		for (unsigned i = j + 1; i < nb_instants; i++)
		{
			somme = 0;
			for (unsigned k = 0; k < j - 1; k++)
			{
				somme = somme + (*matL).vecs[i].comps[k].ampl * (*matU).vecs[k].comps[j].ampl;
			}
			(*matL).vecs[i].comps[j].ampl = ((*matVandermonde).vecs[i].comps[j].ampl - somme) / (*matU).vecs[j].comps[j].ampl;
		}
	}

	// Resolution pour chaque oscillateur
	for (unsigned i_osc = 0; i_osc < nb_osc; i_osc++)
	{
		// Resolution par descente de L * y = currentVec
		t_vecAF *y;
		(*y).comps[0].ampl = (*matB).vecs[i_osc].comps[0].ampl / (*matL).vecs[0].comps[0].ampl;
		(*y).comps[0].freq = (*matB).vecs[i_osc].comps[0].freq / (*matL).vecs[0].comps[0].ampl;
		for (unsigned i = 1; i < nb_instants; i++)
		{
			sommeAF.ampl = 0;
			sommeAF.freq = 0;
			for (unsigned j = 0; j < i; j++)
			{
				sommeAF.ampl += (*matL).vecs[i].comps[j].ampl * (*y).comps[j].ampl;
				sommeAF.freq += (*matL).vecs[i].comps[j].freq * (*y).comps[j].freq;
			}
			(*y).comps[i].ampl = ((*matB).vecs[i_osc].comps[i].ampl - sommeAF.ampl) / (*matL).vecs[i].comps[i].ampl;
			(*y).comps[i].freq = ((*matB).vecs[i_osc].comps[i].freq - sommeAF.freq) / (*matL).vecs[i].comps[i].freq;
		}

		// Resolution par remontee de U * x = y
		t_vecAF *x;
		(*x).comps[nb_instants].ampl = (*y).comps[nb_instants].ampl / (*matU).vecs[nb_instants].comps[nb_instants].ampl;
		(*x).comps[nb_instants].freq = (*y).comps[nb_instants].freq / (*matU).vecs[nb_instants].comps[nb_instants].ampl;
		for (unsigned i = nb_instants - 2; i >= 0; i--)
		{
			sommeAF.ampl = 0;
			sommeAF.freq = 0;
			for (unsigned j = i + 1; j < nb_instants; j++)
			{
				sommeAF.ampl += (*matU).vecs[i].comps[j].ampl * (*x).comps[j].ampl;
				sommeAF.freq += (*matU).vecs[i].comps[j].freq * (*x).comps[j].freq;
			}
			(*x).comps[i].ampl = ((*y).comps[i].ampl - sommeAF.ampl) / (*matU).vecs[i].comps[i].ampl;
			(*x).comps[i].freq = ((*y).comps[i].freq - sommeAF.freq) / (*matU).vecs[i].comps[i].freq;
		}

		// Ajouter x dans bk_osc
		(*bk_osc).vecs[i_osc] = *x;
	}
}
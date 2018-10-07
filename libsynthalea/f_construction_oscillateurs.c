#include <libsynthalea.h>

#include <math.h>

void construction_oscillateurs(
	const double		*idx_temps, 
	const double		*evo_puissance, 
	const double		*evo_dispersion, 
	unsigned			nb_osc, 
	const t_mat			*bk_sp,
	t_mat				*bk_osc)
{
	unsigned nb_instants = sizeof(*idx_temps) / sizeof(double);
	
	

	unsigned							nb_partiels; // > nb_osc
	t_mat								bk_sp_selec;



	////////////////////////////////////////////////////////	Partie aleatoire : trouver le bon spectre pour chaque instant

	// Matrice des spectres selectionnes et ordonnes par ordre chronologique
	alloc_matAF(nb_instants, nb_partiels, bk_sp_selec);






	////////////////////////////////////////////////////////	Suivi des voix a travers les spectres
	
	// Retailler les spectres trouves pour ne garder que les nb_osc premieres composantes
	
	// Tous de taille nb_osc
	t_vec 								bDidCandidatesMatch; // bool
	t_vec								frequencyDistances; // double
	t_vec								iFrequencyDistancesSorted; // int
	
	t_mat								bk_sp_suivi; // AF
	
	
	bk_sp_suivi.vecs[0] = bk_sp_selec.vecs[0];
	for (unsigned i_spectre = 1; i_spectre < nb_instants; i_spectre++)
	{

		//fill(bDidCandidatesMatch, false); fonction a ecrire
		t_vec sortedFrequenciesMemory = sortedFrequencies;
		for (unsigned iComponent = 0; iComponent < nb_osc; iComponent++)
		{
			for (unsigned iCandidate = 0; iCandidate < nb_osc; iCandidate++)
			{
				frequencyDistances[iCandidate] = abs(sortedFrequencies[iComponent]) - sortedFrequenciesMemory.at(iCandidate);
			}

			sort2(frequencyDistances, frequencyDistances, iFrequencyDistancesSorted);

			for (iCandidate = 0; iCandidate < nb_osc; iCandidate++)
			{
				if (bDidCandidatesMatch.at(iFrequencyDistancesSorted[iCandidate]) == false)
				{
					outFrequencies[iFrequencyDistancesSorted[iCandidate]] = sortedFrequencies[iComponent];
					outAmplitudes[iFrequencyDistancesSorted[iCandidate]] = sortedAmplitudes[iComponent];
					bDidCandidatesMatch[iFrequencyDistancesSorted[iCandidate]] = true;
					break;
				}
			}
		}
		sortedFrequencies = outFrequencies;
	}








	/////////////////////////////////////////////////////////	Interpolation
	t_mat 					matVandermonde, 
							matL, 
							matU;

	t_vec 					x, 
							y;

	double 					somme1;
	double 					somme2;

	// Transposition de bk_sp_selec
	t_mat					matB; // = transpose(bk_sp_selec)

	// Construction de la matrice de Vandermonde avec les idx_temps
	alloc_matAF(nb_instants, nb_instants, matVandermonde);
	for (unsigned i = 0; i < nb_instants; i++)
	{
		for (unsigned j = 0; j < nb_instants; j++)
		{
			// La matrice de Vandermonde est identique pour les amplitudes et les fr�quences
			matVandermonde.vecs[i].comps[j].compDOUBLE.val = pow(idx_temps[i], j);
		}
	}


	// Decomposition V = L * U
	for (unsigned j = 0; j < nb_instants; j++)
	{
		matL.vecs[j].comps[j].ampl = 1;
		for (unsigned i = 0; i < j + 1; i++)
		{
			somme1 = 0;
			for (unsigned k = 0; k < i - 1; k++)
			{
				somme1 += matL.vecs[i].comps[k].compAF.ampl * matU.vecs[k].comps[j].compAF.ampl;
			}
			matU.vecs[i].comps[j].compAF.ampl = matVandermonde.vecs[i].comps[j].compAF.ampl - somme1;
		}
		for (unsigned i = j + 1; i < nb_instants; i++)
		{
			somme1 = 0;
			for (unsigned k = 0; k < j - 1; k++)
			{
				somme1 += matL.vecs[i].comps[k].compAF.ampl * matU.vecs[k].comps[j].compAF.ampl;
			}
			matL.vecs[i].comps[j].compAF.ampl = (matVandermonde.vecs[i].comps[j].compAF.ampl - somme1) / matU.vecs[j].comps[j].compAF.ampl;
		}
	}

	// Resolution pour chaque oscillateur
	alloc_matAF(nb_osc, nb_instants, bk_osc);
	for (unsigned i_osc = 0; i_osc < nb_osc; i_osc++)
	{
		// Resolution par descente de L * y = currentVec
		y.comps[0].compAF.ampl = matB.vecs[i_osc].comps[0].compAF.ampl / matL.vecs[0].comps[0].compDOUBLE.val;
		y.comps[0].compAF.freq = matB.vecs[i_osc].comps[0].compAF.freq / matL.vecs[0].comps[0].compDOUBLE.val;
		for (unsigned i = 1; i < nb_instants; i++)
		{
			somme1 = 0;
			somme2 = 0;
			for (unsigned j = 0; j < i; j++)
			{
				somme1 += matL.vecs[i].comps[j].compAF.ampl * y.comps[j].compAF.ampl;
				somme2 += matL.vecs[i].comps[j].compAF.freq * y.comps[j].compAF.freq;
			}
			y.comps[i].compAF.ampl = (matB.vecs[i_osc].comps[i].compAF.ampl - somme1) / matL.vecs[i].comps[i].compAF.ampl;
			y.comps[i].compAF.freq = (matB).vecs[i_osc].comps[i].compAF.freq - somme2) / matL.vecs[i].comps[i].compAF.freq;
		}

		// Resolution par remontee de U * x = y
		x.comps[nb_instants].compAF.ampl = y.comps[nb_instants].compAF.ampl / matU.vecs[nb_instants].comps[nb_instants].compAF.ampl;
		x.comps[nb_instants].compAF.freq = y.comps[nb_instants].freq / matU.vecs[nb_instants].comps[nb_instants].compAF.ampl;
		for (unsigned i = nb_instants - 2; i >= 0; i--)
		{
			somme1 = 0;
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
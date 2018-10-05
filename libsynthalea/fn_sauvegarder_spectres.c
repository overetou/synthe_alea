#include <libsynthalea.h>

#include <stdio.h>

void				sauvegarder_spectres(
						const char *url_collec,
						struct banque_spectres *bk_sp)
{
	std::ofstream ecriture_fichier;
	ecriture_fichier.open(url_collection, std::ios::out);
	if (!ecriture_fichier.is_open()) return false;

	ecriture_fichier << "nom_collection = " << url_collection.c_str << std::endl;
	ecriture_fichier << "nombre_spectres = " << collection_spectres.size() << std::endl;
	ecriture_fichier << std::endl;

	// Ecriture des spectres
	for (unsigned i_spectre = 0; i_spectre < bk_sp->nombre_spectres; i_spectre++)
	{
		ecriture_fichier << "indice_spectre = " << i_spectre << std::endl;
		ecriture_fichier << std::endl;

		// Ecriture des amplitudes
		ecriture_fichier << "amplitudes = " << std::endl;
		for (unsigned i_partiel = 0; i_partiel < bk_sp->collection_spectres[i_spectre]->nombre_partiels; i_partiel++)
		{
			ecriture_fichier << bk_sp->collection_spectres[i_spectre]->partiels_amplitudes[i_partiel] << std::endl;
		}
		ecriture_fichier << std::endl;

		// Ecriture des fr�quences
		ecriture_fichier << "frequences = " << std::endl;
		for (unsigned i_partiel = 0; i_partiel < bk_sp->collection_spectres[i_spectre]->nombre_partiels; i_partiel++) 
		{
			ecriture_fichier << bk_sp->collection_spectres[i_spectre]->partiels_frequences[i_partiel] << std::endl;
		}
		ecriture_fichier << std::endl;

		// Ecriture des caract�ristiques
		ecriture_fichier << "puissance = " << bk_sp->collection_spectres[i_spectre]->puissance << std::endl;
		ecriture_fichier << "dispersion = " << bk_sp->collection_spectres[i_spectre]->dispersion << std::endl;
		ecriture_fichier << std::endl;
	}
	ecriture_fichier.close();
	return true;
}
#include <libsynthalea/libsynthalea.h>

void				charger_spectres(
						const char *url_collec, 
						banque_spectres *bk_sp)
{
	std::ifstream lecture_fichier;
	lecture_fichier.open(url_collection, std::ios::in);
	if (!lecture_fichier.is_open()) return false;
	else
	{
		// charge le contenu du fichier dans collection_spectres
		//ajouter_spectre();
	}
	lecture_fichier.close();
	return true;
}
#include <includes/cl_banque_spectres.h>

#include <iostream>
#include <fstream>

bool salib::banque_spectres::sauvegarder_collection_spectres(
  const std::string &url_collection)
{
  std::ofstream ecriture_fichier;
  ecriture_fichier.open(url_collection, std::ios::out);
  if (!ecriture_fichier.is_open()) return false;

  ecriture_fichier << "nom_collection = " << url_collection << std::endl;
  ecriture_fichier << "nombre_spectres = " << collection_spectres.size() << std::endl;
  ecriture_fichier << std::endl;

  // Ecriture des spectres
  for (std::size_t i_spectre = 0; i_spectre < collection_spectres.size(); i_spectre++)
  {
    ecriture_fichier << "indice_spectre = " << i_spectre << std::endl;
    ecriture_fichier << std::endl;

    // Ecriture des amplitudes
    ecriture_fichier << "amplitudes = " << std::endl;
    for (std::size_t i_partiel = 0; i_partiel < collection_spectres[i_spectre].partiels.size(); i_partiel++)
    {
      ecriture_fichier << collection_spectres[i_spectre].partiels[i_partiel].first << std::endl;
    }
    ecriture_fichier << std::endl;

    // Ecriture des fréquences
    ecriture_fichier << "frequences = " << std::endl;
    for (std::size_t i_partiel = 0; i_partiel < collection_spectres[i_spectre].partiels.size(); i_partiel++)
    {
      ecriture_fichier << collection_spectres[i_spectre].partiels[i_partiel].second << std::endl;
    }
    ecriture_fichier << std::endl;

    // Ecriture des caractéristiques
    ecriture_fichier << "puissance = " << collection_spectres[i_spectre].puissance << std::endl;
    ecriture_fichier << "dispersion = " << collection_spectres[i_spectre].dispersion << std::endl;
    ecriture_fichier << std::endl;
  }
  ecriture_fichier.close();
  return true;
}

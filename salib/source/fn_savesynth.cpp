#include <includes/cl_synth>

#include <iostream>
#include <fstream>

bool salib::synthetiseur::sauvegarder_collection_oscillateurs(
  const std::string &url_collection)
{
  std::ofstream ecriture_fichier;
  ecriture_fichier.open(url_collection, std::ios::out);
  if (!ecriture_fichier.is_open()) return false;

  ecriture_fichier << "nom_preset =" << url_collection << std::endl;
  ecriture_fichier << "nombre_oscillateurs = " << collection_oscillateurs.size() << std::endl;
  ecriture_fichier << "nombre_coefficients = " << collection_oscillateurs[0].size() << std::endl;
  ecriture_fichier << std::endl;

  // Ecriture des oscillateurs
  for (std::size_t i_oscillateur = 0; i_oscillateur < collection_oscillateurs.size(); i_oscillateur++)
  {
    ecriture_fichier << "indice_oscillateur = " << i_oscillateur << std::endl;
    ecriture_fichier << std::endl;

    // Ecriture des amplitudes
    ecriture_fichier << "amplitudes = " << std::endl;
    for (std::size_t i_coefficient = 0; i_coefficient < collection_oscillateurs.size(); i_coefficient++)
    {
      ecriture_fichier << collection_oscillateurs[i_oscillateur][i_coefficient].first << std::endl;
    }
    ecriture_fichier << std::endl;

    // Ecriture des fréquences
    ecriture_fichier << "frequences = " << std::endl;
    for (std::size_t i_coefficient = 0; i_coefficient < collection_oscillateurs.size(); i_coefficient++)
    {
      ecriture_fichier << collection_oscillateurs[i_oscillateur][i_coefficient].second << std::endl;
    }
    ecriture_fichier << std::endl;

  }
  ecriture_fichier.close();
  return true;
}

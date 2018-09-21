#include <includes/cl_synth>

#include <iostream>
#include <fstream>

bool salib::synthetiseur::charger_collection_oscillateurs(
  const std::string &url_collection)
{
  std::ifstream lecture_fichier;
  lecture_fichier.open(url_collection, std::ios::in);
  if (!lecture_fichier.is_open()) return false;

  // lire nombre oscillateurs
  // lire nombre coefficients

  std::size_t nombre_oscillateurs;
  std::size_t nombre_coefficients;

  // Resize de la collection d'oscillateurs
  collection_oscillateurs.resize(nombre_oscillateurs);
  for (std::size_t i_oscillateur = 0; i_oscillateur < nombre_oscillateurs; i_oscillateur++)
  {
    collection_oscillateurs[i_oscillateur].resize(nombre_coefficients);
  }


  for (std::size_t i_oscillateur = 0; i_oscillateur < nombre_oscillateurs; i_oscillateur++)
  {
    // verifier l'indice

    // Lecture des amplitudes
    for (std::size_t i_coefficient = 0; i_coefficient < nombre_coefficients; i_coefficient++)
    {
      lecture_fichier >> collection_oscillateurs[i_oscillateur][i_coefficient].first;
    }

    //

    // Lecture des fréquences
    for (std::size_t i_coefficient = 0; i_coefficient < nombre_coefficients; i_coefficient++)
    {
      lecture_fichier >> collection_oscillateurs[i_oscillateur][i_coefficient].second;
    }

  }

  lecture_fichier.close();
  return true;
}

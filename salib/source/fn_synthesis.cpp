#include <includes/cl_banque_oscillateurs.h>

#include <iostream>
#include <fstream>

bool salib::banque_oscillateurs::synthese(
  const std::size_t indice_echantillon,
  const double frequence,
  const double velocite)
{
  if (collection_oscillateurs.size() == 0) return false; // Collection d'oscillateurs pas encore chargée


  double indice_temporel; // f de indice_echantillon, frequence_echantillonnage

  double indice_puissance;
  double oscillateur_amplitude;
  double oscillateur_frequence;

  double somme_oscillateurs = 0;
  for (std::size_t i_oscillateur = 0; i_oscillateur < collection_oscillateurs.size(); i_oscillateur++)
  {
    oscillateur_amplitude = 0;
    oscillateur_frequence = 0;
    for (std::size_t i_coefficient = 0; i_coefficient < collection_oscillateurs[i_oscillateur].size(); i_coefficient++)
    {
      indice_puissance = std::pow(indice_temporel, i_coefficient);
      oscillateur_amplitude += collection_oscillateurs[i_oscillateur][i_coefficient].first * velocite * indice_puissance;
      oscillateur_frequence += collection_oscillateurs[i_oscillateur][i_coefficient].second * frequence * indice_puissance;
    }
    somme_oscillateurs += oscillateur_amplitude * std::sin(2 * PI * oscillateur_frequence * indice_temporel);
  }

  if (std::abs(somme_oscillateurs) > 1) gain = 1 / std::abs(somme_oscillateurs);
  return somme_oscillateurs * gain;
}
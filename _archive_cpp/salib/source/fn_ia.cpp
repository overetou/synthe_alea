#include <cl_synthetiseur.h>

bool salib::synthetiseur::calcul_collection_oscillateurs(
    const std::vector<double> &indices_temporels,
    const std::vector<double> &evolution_puissance,
    const std::vector<double> &evolution_dispersion,
    const std::size_t nombre_oscillateurs)
{
// Tests

//
  std::size_t nombre_spectres = indices_temporels.size();

// Trouver pour chaque point temporel le spectre le plus approprié en fonction des paramètres de l'utilisateur à ce point

//

  std::vector<std::vector<std::pair<double, double>>> spectres_selectionnes(indices_temporels.size());

  for (std::size_t i_spectre = 0; i_spectre < spectres_selectionnes.size(); i_spectre++)
  {

    // On commence par ne garder que le bon nombre d'oscillateurs
    spectres_selectionnes[i_spectre].resize(nombre_oscillateurs);

    // Suivi des oscillateurs
    if (i_spectre > 0)
    {
      // Parcourt le spectre précédent
      for (std::size_t i_partiel = 0; i_partiel < nombre_oscillateurs; i_partiel++)
      {
        double min_ecart = 10000;
        std::size_t indice_min_ecart;

        // Trouve le partiel le plus proche dans le spectre actuel
        for (std::size_t ii_partiel = i_partiel; ii_partiel < nombre_oscillateurs; ii_partiel++)
        {
          double ecart = std::fabs(spectres_selectionnes[i_spectre][ii_partiel].second - spectres_selectionnes[i_spectre - 1][i_partiel].second);
          if (ecart < min_ecart)
          {
            min_ecart = ecart;
            indice_min_ecart = ii_partiel;
          }
        }
        // Modifier le spectre actuel pour replacer le partiel le plus proche sur la meme ligne que dans le spectre précédent
        // retirer le trouvé du vecteur à		spectres_selectionnes[i_spectre][indice_min_ecart]
        // le rajouter à la position voulue		spectres_selectionnes[i_spectre][i_partiel]
      }
    }
  }

// Construction de la matrice d'interpolation de Vandermonde avec les indices temporels
  // Initialisation
  std::vector<std::vector<std::size_t>> matrice_interpolation(2 * nombre_spectres);
  for (std::size_t i_rang = 0; i_rang < 2 * nombre_spectres; i_rang++) matrice_interpolation[i_rang].resize(nombre_spectres);

  // Remplissage
  for (std::size_t i_rang = 0; i_rang < 2 * nombre_spectres; i_rang++)
  {
    for (std::size_t i_colonne = 0; i_colonne < nombre_spectres; i_colonne++)
    {
      // Augmentation de la matrice
      if (i_rang < nombre_spectres)
      {
        if (i_rang == i_colonne) matrice_interpolation[i_rang][i_colonne] = 1;
        else matrice_interpolation[i_rang][i_colonne] = 0;
      }

      // Matrice de Vandermonde
      else
      {
        matrice_interpolation[nombre_spectres + i_rang][i_colonne] = 0;
      }
    }
  }

// Inversion de la matrice d'interpolation
// Algorithme de gauss


// Calcul pour chaque oscillateur des coefficients du polynôme d'interpolation
  for (std::size_t i_oscillateur = 0; i_oscillateur < nombre_oscillateurs; i_oscillateur++)
  {
    // Pour les amplitudes
      // A^-1 * a
    // Pour les fréquences
      // A^-1 * f
  }
}

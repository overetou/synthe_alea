#pragma once

#include <vector>
#include <utility>

namespace salib
{
  struct spectre
  {
    bool importer_spectre(
      const std::string &url_spectre)
    {
      std::vector<std::pair<double, double>> partiels;
      
      
    }

    double hauteur_enregistrement;

    std::vector<std::pair<double, double>> partiels; // On utilise .first : amplitudes et .second : fréquences
  };

  struct spectre_analyse : public spectre
  {
    bool analyser_spectre(
      const spectre &spectre_brut);

    double puissance;
    double dispersion;
  };
}

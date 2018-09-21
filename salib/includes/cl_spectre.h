#pragma once

namespace salib
{
  struct spectre
  {
    bool importer_spectre(
      const std::string &url_spectre)
    {
      std::vector<std::pair<double, double>> partiels;
      for (std::size_t i_partiel = 0; i_partiel < amplitudes_brutes.size(); i_partiel++)
      {
        partiels.push_back({ amplitudes_brutes[i_partiel], frequences_brutes[i_partiel] });
      }
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

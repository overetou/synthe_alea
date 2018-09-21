#pragma once

namespace salib
{
  class spectre
  {
  public:
    spectre(
      const std::string &url_spectre)
    {
      importer_spectre(url_spectre);
    }

    bool importer_spectre(
      const std::string &url_spectre)
    {
      std::vector<std::pair<double, double>> partiels;
      for (std::size_t i_partiel = 0; i_partiel < amplitudes_brutes.size(); i_partiel++)
      {
        partiels.push_back({ amplitudes_brutes[i_partiel], frequences_brutes[i_partiel] });
      }
    }

  private:
    std::vector<std::pair<double, double>> partiels; // On utilise .first : amplitudes et .second : fréquences
  };
}

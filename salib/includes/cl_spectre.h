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
      const std::string &url_spectre);

  private:
    std::vector<std::pair<double, double>> partiels; // On utilise .first : amplitudes et .second : fréquences
  };
}

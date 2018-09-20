#pragma once

namespace salib
{
  struct spectre
  {
    std::vector<std::pair<double, double>> partiels; // On utilise .first : amplitudes et .second : fréquences

    // Paramètres caractérisant le spectre
    double puissance;
    double dispersion;
  };
}

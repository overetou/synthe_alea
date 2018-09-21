#pragma once

#include "cl_spectre.h"

namespace salib
{
  class spectre_analyse : spectre
  {
  public:
    spectre_analyse(
      const spectre &spectre_brut)
    {
      analyser_spectre(spectre_brut);
    }

    bool analyser_spectre(
      const spectre &spectre_brut);

  private:
    double puissance;
    double dispersion;
  };
}

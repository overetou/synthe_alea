#pragma once

#include "cl_spectre.h"

namespace salib
{
  class spectre_analyse : spectre
  {
  public:
    bool analyser_spectre(
      const spectre &spectre_brut);

  private:
    double puissance;
    double dispersion;
  };
}

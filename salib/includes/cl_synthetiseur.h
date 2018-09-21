#pragma once

#include <cl_banque_oscillateurs.h>

namespace salib
{
  enum parametres_synthese
  {
    frequence_echantillonnage,
    gain
  };

  class synthetiseur : banque_oscillateurs
  {
  public:

    bool modifier_parametre_synthese(
      const std::size_t parametre,
      const double valeur);

    double synthese(
      const std::size_t indice_echantillon,
      const double frequence,
      const double velocite);

  private:

  };
}

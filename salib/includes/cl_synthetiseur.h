#pragma once

#include <cl_banque_spectres.h>
#include <cl_banque_oscillateurs.h>

namespace salib
{
  class synthetiseur : public banque_spectres, public banque_oscillateurs
  {
  public:

    bool calcul_collection_oscillateurs(
  		const std::vector<double> &indices_temporels,
  		const std::vector<double> &evolution_puissance,
  		const std::vector<double> &evolution_dispersion,
  		const std::size_t nombre_oscillateurs);

    bool modifier_frequence_echantillonnage(
      const std::size_t valeur);

    bool modifier_gain(
      const double valeur);

    double synthese(
      const std::size_t indice_echantillon,
      const double frequence,
      const double velocite);

  private:
    int frequence_echantillonnage;
    double gain;
  };
}

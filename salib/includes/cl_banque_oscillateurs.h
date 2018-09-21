#pragma once

#include <cl_banque_spectres.h>
#include <cl_oscillateur.h>

namespace salib
{
  class banque_oscillateurs
  {
  public:
    bool calcul_collection_oscillateurs(
  		const std::vector<double> &indices_temporels,
  		const std::vector<double> &evolution_puissance,
  		const std::vector<double> &evolution_dispersion,
  		const std::size_t nombre_oscillateurs,
      const banque_spectres &banque_spectres_utilisee);

    bool charger_collection_oscillateurs(
      const std::string &url_collection);

    bool sauvegarder_collection_oscillateurs(
      const std::string &url_collection);

  private:
    std::vector<oscillateur> collection_oscillateurs;

  };
}

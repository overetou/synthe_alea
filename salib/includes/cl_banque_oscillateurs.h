#pragma once

#include <cl_banque_spectres.h>
#include <cl_oscillateur.h>

namespace salib
{
  enum parmetres_synthese
  {
    frequence_echantillonnage,
    gain
  };

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

    bool modifier_parametre_synthese(
      const std::size_t parametre,
      const double valeur);

    double synthese(
      const std::size_t indice_echantillon,
      const double frequence,
      const double velocite);

  private:
    std::vector<oscillateur> collection_oscillateurs;
  };
}

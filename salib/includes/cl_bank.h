#pragma once

#include <st_spectra>

namespace salib
{
  class banque
  {
  public:
    bool charger_collection_spectres(
      const std::string &url_collection);

    bool sauvegarder_collection_spectres(
      const std::string &url_collection);

    bool ajouter_spectre_dans_la_collection(
      const std::vector<double> &amplitudes_brutes,
      const std::vector<double> &frequences_brutes,
      const double hauteur_enregistrement);

  private:
    std::vector<spectre> collection_spectres;



  };
}

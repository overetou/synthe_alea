#pragma once

#include <cl_spectre_analyse.h>

namespace salib
{
  class banque_spectres
  {
  public:
    bool charger_collection_spectres(
      const std::string &url_collection);

    bool sauvegarder_collection_spectres(
      const std::string &url_collection);

    bool ajouter_spectre_dans_la_collection(
      const spectre_analyse &nouveau_spectre);

  private:
    std::vector<spectre> collection_spectres;



  };
}

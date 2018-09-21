#pragma once

#include <cl_banque_spectres.h>
#include <cl_oscillateur.h>

namespace salib
{
  class banque_oscillateurs
  {
  public:
    bool charger_collection_oscillateurs(
      const std::string &url_collection);

    bool sauvegarder_collection_oscillateurs(
      const std::string &url_collection);

  protected:
    std::vector<oscillateur> collection_oscillateurs;
  };
}

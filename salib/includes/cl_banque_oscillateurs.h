#pragma once

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

    bool fusionner_avec(
      const banque_oscillateurs &nouvelle_banque_oscillateurs);

  protected:
    std::vector<oscillateur> collection_oscillateurs;
  };
}

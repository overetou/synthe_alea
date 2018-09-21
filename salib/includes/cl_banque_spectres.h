#pragma once

#include <cl_spectre.h>

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
      const spectre_analyse &nouveau_spectre_analyse)
    {
      collection_spectres.push_back(nouveau_spectre_analyse);
    }
    bool ajouter_spectre_dans_la_collection(
      const spectre &nouveau_spectre)
    {
      spectre_analyse nouveau_spectre_analyse;
      nouveau_spectre_analyse.analyser_spectre(nouveau_spectre);

      return ajouter_spectre_dans_la_collection(nouveau_spectre_analyse);
    }
    bool ajouter_spectre_dans_la_collection(
      const std::string &url_spectre)
    {
      spectre nouveau_spectre;
      nouveau_spectre.importer_spectre(url_spectre);

      return ajouter_spectre_dans_la_collection(nouveau_spectre);
    }

  protected:
    std::vector<spectre_analyse> collection_spectres;



  };
}

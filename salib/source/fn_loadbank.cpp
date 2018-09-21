#include <includes/cl_bank>

#include <iostream>
#include <fstream>

bool salib::banque::charger_collection_spectres(
  const std::string &url_collection)
{
  std::ifstream lecture_fichier;
  lecture_fichier.open(url_collection, std::ios::in);
  if (!lecture_fichier.is_open()) return false;
  else
  {
    // charge le contenu du fichier dans collection_spectres
    //ajouter_spectre();
  }
  lecture_fichier.close();
  return true;
}

#pragma once

#include <sg_database>
#include <st_spectra>

namespace salib
{
  //
  bool ajouter_spectre_dans_la_collection(
    const std::vector<double> &amplitudes_brutes,
    const std::vector<double> &frequences_brutes,
    const double hauteur_enregistrement);
}

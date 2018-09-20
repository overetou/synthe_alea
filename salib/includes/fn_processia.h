#pragma once

#include <sg_database>
#include <sg_synth>
#include <st_spectra>
#include <st_osc>

namespace salib
{
  //
  bool calcul_collection_oscillateurs(
			const std::vector<double> &indices_temporels,
			const std::vector<double> &evolution_puissance,
			const std::vector<double> &evolution_dispersion,
			const std::size_t nombre_oscillateurs);
}

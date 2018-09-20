#pragma once

#include <sg_synth>
#include <st_osc>

namespace salib
{
  double synthese(
    const std::size_t indice_echantillon,
    const double frequence,
    const double velocite);
}

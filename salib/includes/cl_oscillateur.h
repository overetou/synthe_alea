#pragma once

#include <vector>
#include <utility>

namespace salib
{
  struct oscillateur
  {
    std::vector<std::pair<double, double>> coefficients_lagrange;
    
  };
}

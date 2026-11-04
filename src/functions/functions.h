#pragma once 
#include <vector>
#include <array>

namespace functions {
  std::vector<float> lorenzAttractor(int nPoints, double dt, double sigma, double rho, double beta, std::array<float, 3> start);
}

  


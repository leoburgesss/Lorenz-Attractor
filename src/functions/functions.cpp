#include "functions.h"
#include <cmath>
#include <vector>
#include <array>

namespace functions{

std::vector<float> lorenzAttractor(int nPoints, double dt, double sigma, double rho, double beta, std::array<float, 3> start){
  std::vector<float> points;  points.reserve(3*nPoints);
  float x = start[0]; float y = start[1]; float z = start[2];
  points.push_back(x); points.push_back(y); points.push_back(z);

  for(int i{1}; i < nPoints; ++i){
    double dx1 = sigma * (y - x);
    double dy1 = x * (rho - z) - y;
    double dz1 = x * y - beta * z;

    double x2 = x + 0.5*dt*dx1;  double y2 = y + 0.5*dt*dy1;  double z2 = z + 0.5*dt*dz1;
    double dx2 = sigma * (y2 - x2);
    double dy2 = x2 * (rho - z2) - y2;
    double dz2 = x2 * y2 - beta * z2;


    double x3 = x + 0.5*dt*dx2;  double y3 = y + 0.5*dt*dy2; double z3 = z + 0.5*dt*dz2;
    double dx3 = sigma * (y3 - x3);
    double dy3 = x3 * (rho - z3) - y3;
    double dz3 = x3 * y3 - beta * z3;

    double x4 = x + dt*dx3;  double y4 = y + dt*dy3;  double z4 = z + dt*dz3;
    double dx4 = sigma * (y4 - x4);
    double dy4 = x4 * (rho - z4) - y4;
    double dz4 = x4 * y4 - beta * z4;

    x += (dt/6) * (dx1 + 2*dx2 + 2*dx3 + dx4);
    y += (dt/6) * (dy1 + 2*dy2 + 2*dy3 + dy4);
    z += (dt/6) * (dz1 + 2*dz2 + 2*dz3 + dz4);

    points.push_back(x); points.push_back(y); points.push_back(z);

 
  }

  return points;
}
}


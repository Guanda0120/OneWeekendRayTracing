#ifndef RT_CONSTANCE_H
#define RT_CONSTANCE_H

#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <cstdlib>

// C++ Std Usings
using std::make_shared;
using std::shared_ptr;

// Constants

const double pi = 3.1415926535897932385;

const double absolute_error = 1e-160;

const double NEAR_ZERO_BUF = 1e-3;

// Utility Functions
inline double degrees_to_radians(double degrees) {
  return degrees * pi / 180.0;
}

inline double random_double(){
  // std::rand() return a max value is 0x7fff where is 32767
  return std::rand()/(RAND_MAX+1.0);
}

inline double random_double(double min, double max){
  return min+(max-min)*random_double();
}

enum axis{
  X=0,
  Y=1,
  Z=2
};

struct uv{
  double u;
  double v;
  uv(double u, double v): u(u), v(v){};
};

// Common Headers


#endif
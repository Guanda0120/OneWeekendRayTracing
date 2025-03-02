#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include "vec3.h"

class perlin_noise{
  private:
    static const int point_count = 256;
    double scale_;
    double randfloat_[point_count];
    int perm_x_[point_count];
    int perm_y_[point_count];
    int perm_z_[point_count];
    static void perlin_generate_perm(int* p);
    static void permute(int* p);
  public:
    perlin_noise(double scale);
    double noise(const point& p) const;
};

#endif
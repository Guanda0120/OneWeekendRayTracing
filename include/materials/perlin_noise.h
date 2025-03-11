#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include "vec3.h"

class perlin_noise{
  private:
    static const int point_count = 256;
    vec3 randvec_[point_count];
    int perm_x_[point_count];
    int perm_y_[point_count];
    int perm_z_[point_count];
    static void perlin_generate_perm(int* p);
    static void permute(int* p);
    static double perlin_interp(const vec3 c[2][2][2], double u, double v, double w);
  public:
    perlin_noise();
    double noise(const point& p) const;
    double turb(const point& p, int depth) const;
};

#endif
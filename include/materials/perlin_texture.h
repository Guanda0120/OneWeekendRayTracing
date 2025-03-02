#ifndef PERLIN_TEXTURE_H
#define PERLIN_TEXTURE_H

#include "materials/texture.h"
#include "materials/perlin_noise.h"

class perlin_texture: public texture{
  public:
    perlin_texture(double scale);
    ~perlin_texture();
    color value(double u, double v, const point& p) const override;
  private:
    perlin_noise noise;
};

#endif
#include "materials/perlin_texture.h"

perlin_texture::perlin_texture(double scale) : noise(scale) {}

perlin_texture::~perlin_texture(){}

color perlin_texture::value(double u, double v, const point& p) const{
  double color_ratio=this->noise.noise(p);
  return color(color_ratio*1,color_ratio*1,color_ratio*1);
}
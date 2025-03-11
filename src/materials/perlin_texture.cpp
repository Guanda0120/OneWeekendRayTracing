#include "materials/perlin_texture.h"

perlin_texture::perlin_texture(double scale) : noise(), scale_(scale) {}

perlin_texture::~perlin_texture(){}

color perlin_texture::value(double u, double v, const point& p) const{
  
  auto fac = this->noise.turb(p, 7);
  return color(1*fac, 1*fac, 1*fac);
  // double color_ratio=1.0+this->noise.noise(p*this->scale_);
  // return color(color_ratio*0.5,color_ratio*0.5,color_ratio*0.5);
}
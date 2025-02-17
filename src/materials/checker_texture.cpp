#include "materials/checker_texture.h"

checker_texture::checker_texture(double scale, const color& odd_c, const color& even_c){
  this->even_t_ = new solid_color(even_c);
  this->odd_t_ = new solid_color(odd_c);
  this->scale_factor_ = scale;
}

checker_texture::~checker_texture(){
  // Manually delete texture
  delete this->even_t_;
  delete this->odd_t_;
}

color checker_texture::value(double u, double v, const point& p) const {
  int x_i = int(std::floor(this->scale_factor_*p.x()));
  int y_i = int(std::floor(this->scale_factor_*p.y()));
  int z_i = int(std::floor(this->scale_factor_*p.z()));
  int idx = (x_i+y_i+z_i)%2;
  return idx==0? this->even_t_->value(u,v,p):this->odd_t_->value(u,v,p);
}

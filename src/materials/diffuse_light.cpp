#include "materials/diffuse_light.h"


diffuse_light::diffuse_light(texture* tex): tex_(tex) {}


diffuse_light::diffuse_light(const color color){
  this->tex_ = new solid_color(color);
}

diffuse_light::~diffuse_light(){
  delete this->tex_;
}

color diffuse_light::emitted(double u, double v, const point& p) const {
  return this->tex_->value(u,v,p);
}
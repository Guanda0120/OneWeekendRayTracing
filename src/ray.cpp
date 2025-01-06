#include "ray.h"

ray::ray(vec3& origin, vec3& direc):
  origin_(origin), direc_(direc){}

ray::~ray(){}

vec3& ray::origin() const{
  return this->origin_;
}

vec3& ray::direction() const{
  return this->direc_;
}

vec3 ray::at(double t) const {
  return this->origin_+t*this->direc_;
}
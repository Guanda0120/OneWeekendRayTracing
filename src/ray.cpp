#include "ray.h"

ray::ray(){
  origin_ = vec3();
  direc_ = vec3();
};

ray::ray(const vec3& origin, const vec3& direc):
  origin_(origin), direc_(direc){}

ray::~ray(){}

vec3 ray::origin() const{
  return this->origin_;
}

vec3 ray::direction() const{
  return this->direc_;
}

vec3 ray::at(double t) const {
  return this->origin_+t*this->direc_;
}
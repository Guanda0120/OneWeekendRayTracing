#include "ray.h"

ray::ray(vec3& origin, vec3& direc):
  origin_(origin), direc_(direc){}

ray::~ray(){}

const vec3& ray::origin(){
  return this->origin_;
}

const vec3& ray::direction(){
  return this->direc_;
}

const vec3 ray::at(double t){
  return this->origin_+t*this->direc_;
}
#include "include/vec3.h"

vec3::vec3() : e{0.0, 0.0, 0.0} {};

vec3::vec3(double x, double y, double z): e{x, y, z} {};

/* negative the vector */
vec3 vec3::operator-() const {
  return vec3(-this->e[0], -this->e[1], -this->e[2]);
}

/// @brief Index the e
/// @param i the index value
/// @return 
double vec3::operator[](int i) const {
  return this->e[i];
}

/// @brief Just modify the object itself with the effect of const v
/// @param v the vector to be add on
/// @return self ptr and modify 
vec3& vec3::operator+=(const vec3& v) {
  this->e[0] += v[0];
  this->e[1] += v[1];
  this->e[2] += v[2];
  return *this;
}

double vec3::length() const{
  std::sqrt(this->e[0]*this->e[0] + this->e[1]*this->e[1] + this->e[2]*this->e[2]);
}
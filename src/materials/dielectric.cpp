#include "materials/dielectric.h"

dielectric::dielectric(double refraction_index): refraction_index_(refraction_index){}

bool dielectric::scatter(const ray& r_in, const point& p, const vec3& normal, color& attenuation, ray& scattered) const {
  vec3 para_in = -dot(r_in.direction(), normal)*normal;
  vec3 ortho_in = normal-para_in;
  // ortho_out = 
  return true;
};

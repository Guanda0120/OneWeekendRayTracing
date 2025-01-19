#include "materials/metal.h"

metal::metal(const color& albedo, double fuzz):albedo_(albedo){
  if (fuzz == -1.0){
    this->is_fuzz_=false;
    this->fuzz_coe_=0.0;
  } else {
    this->is_fuzz_=true;
    this->fuzz_coe_=fuzz;
  }
};

bool metal::scatter(const ray& r_in, const point& p, const vec3& normal, color& attenuation, ray& scattered) const {
  vec3 reflected = reflect(r_in.direction(), normal);
  reflected.normalize_vec();
  if (this->is_fuzz_){
    reflected+=this->fuzz_coe_*random_unit_vector();
    reflected.normalize_vec();
  }
  scattered = ray(p, reflected);
  attenuation = albedo_;
  return true;
};

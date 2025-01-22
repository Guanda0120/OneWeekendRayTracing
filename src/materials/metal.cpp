#include "materials/metal.h"

metal::metal(const color& albedo, string mat_name, double fuzz)
  :albedo_(albedo){
  this->name = mat_name;
  if (fuzz == -1.0){
    this->is_fuzz_=false;
    this->fuzz_coe_=0.0;
  } else {
    this->is_fuzz_=true;
    this->fuzz_coe_=fuzz;
  }
};

bool metal::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
  vec3 reflected = reflect(r_in.direction(), rec.normal);
  reflected.normalize_vec();
  if (this->is_fuzz_){
    reflected+=this->fuzz_coe_*random_unit_vector();
    reflected.normalize_vec();
  }
  scattered = ray(rec.p, reflected);
  attenuation = albedo_;
  return true;
};

#include "materials/dielectric.h"

dielectric::dielectric(double refraction_index, string mat_name)
  :refraction_index_(refraction_index){
    this->name = mat_name;
}

bool dielectric::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
  attenuation = color(1.0, 1.0, 1.0);
  double ri = rec.front_face ? (1.0/this->refraction_index_) : this->refraction_index_;
  vec3 unit_direction = r_in.direction();
  vec3 refracted = refract(unit_direction, rec.normal, ri);
  scattered = ray(rec.p, refracted);
  return true;
};

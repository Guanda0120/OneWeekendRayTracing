#include "materials/dielectric.h"

dielectric::dielectric(double refraction_index, string mat_name)
  :refraction_index_(refraction_index){
    this->name = mat_name;
}

bool dielectric::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
  attenuation = color(1.0, 1.0, 1.0);
  double ri = rec.front_face ? (1.0/this->refraction_index_) : this->refraction_index_;
  vec3 unit_direction = r_in.direction();
  double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
  double sin_theta = std::sqrt(1.0 - cos_theta*cos_theta);
  bool cannot_refract = ri * sin_theta > 1.0;
  vec3 direction;
  if (cannot_refract)
      direction = reflect(unit_direction, rec.normal);
  else
      direction = refract(unit_direction, rec.normal, ri);
  scattered = ray(rec.p, direction, r_in.time());
  return true;
};

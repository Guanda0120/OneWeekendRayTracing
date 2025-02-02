#include "materials/lambertian.h"

lambertian::lambertian(const color& albedo, string mat_name)
  :albedo_(albedo){
    this->name = mat_name;
};

bool lambertian::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
  auto scatter_direction = rec.normal + random_unit_vector_hemisphere(rec.normal);
  scatter_direction.normalize_vec();
  scattered = ray(rec.p, scatter_direction, r_in.time());
  attenuation = this->albedo_;
  return true;
};

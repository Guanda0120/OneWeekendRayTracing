#include "materials/lambertian.h"

lambertian::lambertian(const color& albedo):albedo_(albedo){};

bool lambertian::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
  auto scatter_direction = rec.normal + random_unit_vector_hemisphere(rec.normal);
  scatter_direction.normalize_vec();
  scattered = ray(rec.p, scatter_direction);
  attenuation = this->albedo_;
  return true;
};

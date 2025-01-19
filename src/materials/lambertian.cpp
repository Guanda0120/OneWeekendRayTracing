#include "materials/lambertian.h"

lambertian::lambertian(const color& albedo):albedo_(albedo){};

bool lambertian::scatter(const ray& r_in, const point& p, const vec3& normal, color& attenuation, ray& scattered) const {
  auto scatter_direction = normal + random_unit_vector_hemisphere(normal);
  scatter_direction.normalize_vec();
  scattered = ray(p, scatter_direction);
  attenuation = this->albedo_;
  return true;
};

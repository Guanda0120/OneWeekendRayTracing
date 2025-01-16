#include "materials/metal.h"

metal::metal(const color& albedo):albedo_(albedo){};

bool metal::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
  vec3 reflected = reflect(r_in.direction(), rec.normal);
  reflected.normalize_vec();
  scattered = ray(rec.p, reflected);
  attenuation = albedo_;
  return true;
};

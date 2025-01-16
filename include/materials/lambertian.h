#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "materials/material.h"

class lambertian:public material {
  public:
    lambertian(const color& albedo);
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

  private:
    color albedo_;
};

#endif
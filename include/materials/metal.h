#ifndef METAL_H
#define METAL_H

#include "materials/material.h"

class metal: public material{
  public:
    metal(const color& albedo, double fuzz=-1.0);
    bool scatter(const ray& r_in, const point& p, const vec3& normal, color& attenuation, ray& scattered) const override;
  private:
    color albedo_;
    bool is_fuzz_;
    double fuzz_coe_;
};

#endif
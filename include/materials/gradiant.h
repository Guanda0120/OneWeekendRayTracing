#ifndef GRADIANT_H
#define GRADIANT_H

#include "materials/material.h"

class gradiant: public material{
  public:
    gradiant(color from, color to, string name);
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

  private: 
    color from_c_;
    color to_c_;
};

#endif
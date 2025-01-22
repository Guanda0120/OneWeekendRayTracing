#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "materials/material.h"

class dielectric: public material{
  public:
    /// @brief Constructor of dielectric
    /// @param albedo The color of refraction
    /// @param refraction_index The refraction Index (eta)
    dielectric(double refraction_index, string mat_name);
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;

  private:
    /// @brief The eta for refraction
    double refraction_index_;
};

#endif
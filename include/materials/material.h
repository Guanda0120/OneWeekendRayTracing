#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "hittable.h"
#include "color.h"

class material{
  public:
    virtual ~material()=default;
    /// @brief 
    /// @param r_in 
    /// @param rec 
    /// @param attenuation 
    /// @param scattered 
    /// @return 
    virtual bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const;
};

#endif
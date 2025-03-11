#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "color.h"
#include "hit_record.h"
#include <string>

using std::string;

class hit_record;

/// @brief A material need to be create by factory not a self init
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
    /// @brief 
    /// @param u 
    /// @param v 
    /// @param p 
    /// @return 
    virtual color emitted(double u, double v, const point& p) const;
    /// @brief The material name
    string name;  
};

#endif
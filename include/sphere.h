#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "hittable.h"
#include "materials/material.h"

class sphere: public hittable
{
  private:
    /* Sphere radius and center point */
    double radius_;
    point center_;
    material* mat_;

  public:
    sphere(const point& c, double r, material* mat);
    bool hit(const ray& r, interval domain, hit_record& rec) const override ;
    
    /// @brief Dont delete the material, material will be deleted by material manager
    ~sphere();
};

#endif
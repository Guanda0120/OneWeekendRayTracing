#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "hittable.h"

class sphere: public hittable
{
  private:
    /* Sphere radius and center point */
    double radius;
    point center;

  public:
    sphere(double r, point& center);
    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override ;
    ~sphere();
};

#endif
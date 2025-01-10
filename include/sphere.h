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
    sphere(const point& c, double r);
    bool hit(const ray& r, interval domain, hit_record& rec) const override ;
    ~sphere();
};

#endif
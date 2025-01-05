#ifndef HITTABLE_h
#define HITTABLE_h

#include "vec3.h"
#include "ray.h"

using point = vec3;

struct hit_record{
  public:
    point p;
    vec3 normal;
    double t;
};

class hittable{
  public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif
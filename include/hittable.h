#ifndef HITTABLE_h
#define HITTABLE_h

#include "vec3.h"
#include "ray.h"

using point = vec3;

struct hit_record{
  public:
    /// @brief Hit Point 
    point p;
    /// @brief Normal Direction oft the plane normal direction
    vec3 normal;
    /// @brief the t of insert ray
    double t;
    /// @brief Is the face the front face
    bool front_face;
};

class hittable{
  public:
    virtual ~hittable() = default;
    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif
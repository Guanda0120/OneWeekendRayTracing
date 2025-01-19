#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include <memory>
#include "vec3.h"
#include "materials/material.h"

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
    /// @brief The material of hit point
    std::shared_ptr<material> mat;
};

#endif
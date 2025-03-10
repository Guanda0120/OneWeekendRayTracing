#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include "vec3.h"
#include "materials/material.h"

class material;

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
    material* mat;
    /// @brief The texture U
    double u;
    /// @brief The texture V
    double v;
};

#endif
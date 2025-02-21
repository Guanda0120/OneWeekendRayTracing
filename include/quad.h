#ifndef QUAD_H
#define QUAD_H

#include "hittable.h"
#include "algorithm"

class quad: public hittable{  
  private:
    bounding_box b_box_;
    point p_;
    vec3 u_;
    vec3 v_;
    vec3 normal_;
    vec3 w_;
    material* mat_;
    bool factor_contains_(double alpha, double beta, uv uv_info) const;

  public: 
    /// @brief 
    /// @param p A point on quad 
    /// @param u Vec not normalized, has width!
    /// @param v Vec not normalized, has width!
    /// @param m MAterial
    quad(point p, vec3 u, vec3 v, material* m);
    ~quad();
    bounding_box b_box() const override;
    bool hit(const ray& r, interval domain, hit_record& rec) const override;
};

#endif
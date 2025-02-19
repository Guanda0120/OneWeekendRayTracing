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
    vec3 move_direc_;
    bounding_box b_box_;
    uv get_sphere_uv(const point& p) const;

  public:
    
    /// @brief Statable Sphere
    /// @param c the station center
    /// @param r radius
    /// @param mat material
    sphere(const point& c, double r, material* mat);

    /// @brief Movable Sphere
    /// @param st start point
    /// @param ed end point
    /// @param r radius
    /// @param mat material
    sphere(const point& st, const point& ed, double r, material* mat);
    
    /// @brief 
    /// @param r 
    /// @param domain 
    /// @param rec 
    /// @return 
    bool hit(const ray& r, interval domain, hit_record& rec) const override ;
    
    /// @brief Get the sphere b_box
    /// @return 
    bounding_box b_box() const override;

    /// @brief Dont delete the material, material will be deleted by material manager
    ~sphere();
};

#endif
#include "sphere.h"


sphere::sphere(double r, point& c):
  radius(r), center(c) {};

sphere::~sphere() = default;

/// @brief Check the sphere is hitted by the ray
/// @param r The sphere radius
/// @param ray_tmin 
/// @param ray_tmax 
/// @param rec 
/// @return 
bool sphere::hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const {
  // This algorithm may have this bug
  /**
   * If the camera is inside the sphere, and it have two root
   * the abs of neg factor is larger than pos one
   * this will consider to be a false case
   * Indeed it is a true one
   * vec3 vec_sphere = this->center - r.origin();
   * Project the vec to ray direc
   * double factor =  dot(vec_sphere, r.direction());
   * vec3 dist_vec = vec_sphere-factor*r.direction();
   * double dist = dist_vec.length();
   */
  
  vec3 vec_sphere = this->center - r.origin();
  // Project the vec to ray direc
  double factor =  dot(vec_sphere, r.direction());
  vec3 dist_vec = vec_sphere-factor*r.direction();
  double dist = dist_vec.length();
  if (dist<=this->radius && factor>0){
    // Get the inter point 
    point near_inter;
    // 
    rec.p = near_inter;
    rec.normal = near_inter-this->center;
    rec.t = 10.;
    return true;
  } 
  return false;
}

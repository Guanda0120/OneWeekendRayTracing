#include "sphere.h"


sphere::sphere(const point& c, double r):
  radius(r), center(c) {};

sphere::~sphere() = default;

/// @brief Check the sphere is hitted by the ray
/// @param r The sphere radius
/// @param ray_tmin 
/// @param ray_tmax 
/// @param rec 
/// @return 
bool sphere::hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const {

  vec3 vec_sphere = this->center-r.origin();
  // Project the vec to ray direc
  double factor = dot(vec_sphere, r.direction());
  vec3 dist_vec = vec_sphere-factor*r.direction();
  double dist = dist_vec.length();
  if (dist<=this->radius && factor>0){
    double t = std::sqrt(this->radius*this->radius-dist*dist);
    // 
    rec.p = r.direction()*-t+dist_vec+this->center;
    rec.normal = rec.p-this->center;
    rec.normal.normalize_vec();
    rec.t = (rec.p-r.origin()).length();
    rec.front_face = dot(rec.normal, r.direction())<0;
    return true;
  } 
  return false;
}

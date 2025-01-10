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
bool sphere::hit(const ray& r, interval domain, hit_record& rec) const {

  vec3 vec_sphere = this->center-r.origin();
  // Project the vec to ray direc
  double factor = dot(vec_sphere, r.direction());
  vec3 dist_vec = vec_sphere-factor*r.direction();
  double dist = dist_vec.length();
  if (dist<=this->radius && factor>0){
    double t = std::sqrt(this->radius*this->radius-dist*dist);
    point near_pt =  r.direction()*-t+dist_vec+this->center;
    double ray_len = (near_pt-r.origin()).length();
    if (domain.contains(ray_len)){
      return false;
    }
    rec.p =near_pt;
    rec.normal = rec.p-this->center;
    rec.normal.normalize_vec();
    rec.t = ray_len;
    rec.front_face = dot(rec.normal, r.direction())<0;
    return true;
  } 
  return false;
}

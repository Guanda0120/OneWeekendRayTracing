#include "sphere.h"


sphere::sphere(const point& c, double r, material* mat):
  radius_(r), center_(c), mat_(mat) {};

sphere::~sphere() = default;

/// @brief Check the sphere is hitted by the ray
/// @param r The sphere radius
/// @param ray_tmin 
/// @param ray_tmax 
/// @param rec 
/// @return 
bool sphere::hit(const ray& r, interval domain, hit_record& rec) const {

  vec3 vec_sphere = this->center_-r.origin();
  // Project the vec to ray direc
  double factor = dot(vec_sphere, r.direction());
  vec3 dist_vec = factor*r.direction()-vec_sphere;
  double dist = dist_vec.length();
  if (dist<=this->radius_ && factor>0){

    double t = std::sqrt(this->radius_*this->radius_-dist*dist);
    point near_pt =  this->center_+dist_vec-r.direction()*t;
    double ray_len = (near_pt-r.origin()).length();

    if (!domain.contains(ray_len)){
      return false;
    }
    // Just self
    if ((near_pt-r.origin()).length()<NEAR_ZERO_BUF){
      near_pt =  this->center_+dist_vec+r.direction()*t;
      ray_len = (near_pt-r.origin()).length();
      if (!domain.contains(ray_len)){
        return false;
      }
    }
    rec.p =near_pt;
    rec.normal = rec.p-this->center_;
    rec.normal.normalize_vec();
    rec.t = ray_len;
    rec.mat = this->mat_;
    rec.front_face = dot(rec.normal, r.direction())<0;
    rec.normal = rec.front_face? rec.normal:-rec.normal;
    return true;
  } 
  return false;
}

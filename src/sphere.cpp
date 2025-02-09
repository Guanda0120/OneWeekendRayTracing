#include "sphere.h"


sphere::sphere(const point& c, double r, material* mat):
  radius_(r), center_(c), mat_(mat) {
  this->move_direc_ = vec3(0.0, 0.0, 0.0);
  point min_pt = point(c.e[0]-r,c.e[1]-r,c.e[2]-r);
  point max_pt = point(c.e[0]+r,c.e[1]+r,c.e[2]+r);
  this->b_box_ = bounding_box(min_pt, max_pt);
};

sphere::sphere(const point& st, const point& ed, double r, material* mat):
  radius_(r), center_(st), mat_(mat) {
  this->move_direc_ = ed-st;
  // this->move_direc_.normalize_vec();
  vec3 radius_vec = vec3(r,r,r);
  bounding_box st_box = bounding_box(st-radius_vec, st+radius_vec);
  bounding_box ed_box = bounding_box(ed-radius_vec, ed+radius_vec);
  this->b_box_ = bounding_box(st_box, ed_box);
};

sphere::~sphere() = default;

/// @brief Check the sphere is hitted by the ray
/// @param r The sphere radius
/// @param ray_tmin 
/// @param ray_tmax 
/// @param rec 
/// @return 
bool sphere::hit(const ray& r, interval domain, hit_record& rec) const {
  point cur_cen = r.time()*this->move_direc_+this->center_;
  vec3 vec_sphere = cur_cen-r.origin();
  // Project the vec to ray direc
  double factor = dot(vec_sphere, r.direction());
  vec3 dist_vec = factor*r.direction()-vec_sphere;
  double dist = dist_vec.length();
  if (dist<=this->radius_ && factor>0){

    double t = std::sqrt(this->radius_*this->radius_-dist*dist);
    point near_pt =  cur_cen+dist_vec-r.direction()*t;
    double ray_len = (near_pt-r.origin()).length();

    if (!domain.contains(ray_len)){
      return false;
    }
    // Just self
    if ((near_pt-r.origin()).length()<NEAR_ZERO_BUF){
      near_pt = cur_cen+dist_vec+r.direction()*t;
      ray_len = (near_pt-r.origin()).length();
      if (!domain.contains(ray_len)){
        return false;
      }
    }
    rec.p =near_pt;
    rec.normal = rec.p-cur_cen;
    rec.normal.normalize_vec();
    rec.t = ray_len;
    rec.mat = this->mat_;
    rec.front_face = dot(rec.normal, r.direction())<0;
    rec.normal = rec.front_face? rec.normal:-rec.normal;
    return true;
  } 
  return false;
}

bounding_box sphere::b_box() const {
  return this->b_box_;
}
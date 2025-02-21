#include "quad.h"

quad::quad(point p, vec3 u, vec3 v, material* m):p_(p), u_(u), v_(v), mat_(m){
  bounding_box b1 = bounding_box(p+u, p+v);
  bounding_box b2 = bounding_box(p, p+v+u);
  this->b_box_ = bounding_box(b1, b2);
  vec3 n = cross(u_, v_);
  this->w_=n/dot(n,n);
  this->normal_=n;
  this->normal_.normalize_vec();
}

bool quad::hit(const ray& r, interval ray_t, hit_record& rec) const{
  // Find intersection with infinite plane
  // Ax+By+Cz = D
  // Just set the p into function above
  // if the nd = 0; just return 0
  double denom = dot(r.direction(), this->normal_);
  if (std::fabs(denom)<NEAR_ZERO_BUF){
    return false;
  }
  // Check Ray factor
  double factor = (dot(this->p_, this->normal_)-dot(r.origin(), this->normal_))/dot(r.direction(), this->normal_);
  if (factor<=NEAR_ZERO_BUF){
    return false;
  }
  point hit_pt = r.at(factor);
  // alpha: factor on u
  // beta: factor on v
  vec3 dir_pt = hit_pt - this->p_;
  double alpha = dot(this->w_, cross(dir_pt, this->v_));
  double beta = dot(this->w_, cross(this->u_, dir_pt));
  uv uv_;
  if (this->factor_contains_(alpha, beta, uv_)){
    return false;
  }
  rec.t = factor;
  rec.p = hit_pt;
  rec.u = uv_.u;
  rec.v = uv_.v;
  rec.mat = this->mat_;
  rec.normal = this->normal_;
  rec.front_face=dot(rec.normal, r.direction())<0;
  return true;
}

bool quad::factor_contains_(double alpha, double beta, uv uv_info) const {
  interval unit_interval = interval(0, 1);
  // Given the hit point in plane coordinates, return false if it is outside the
  // primitive, otherwise set the hit record UV coordinates and return tru
  if (!unit_interval.contains(alpha) || !unit_interval.contains(beta))
      return false;
  uv_info = uv(alpha, beta);
  return true;
}

bounding_box quad::b_box() const {
  return this->b_box_;
}

quad::~quad(){}
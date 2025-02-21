#include "bounding_box.h"

bounding_box::bounding_box(point pt1, point pt2){
  this->x_domain = interval(std::min(pt1.x(), pt2.x()), std::max(pt1.x(), pt2.x()));
  this->y_domain = interval(std::min(pt1.y(), pt2.y()), std::max(pt1.y(), pt2.y()));
  this->z_domain = interval(std::min(pt1.z(), pt2.z()), std::max(pt1.z(), pt2.z()));
  this->max_pt = point(this->x_domain.max, this->y_domain.max, this->z_domain.max);
  this->min_pt = point(this->x_domain.min, this->y_domain.min, this->z_domain.min);
  this->padding_minimums();
}

bounding_box::bounding_box(const bounding_box& box1, const bounding_box& box2){
  double min_x = std::min(box1.min_pt.e[0], box2.min_pt.e[0]);
  double min_y = std::min(box1.min_pt.e[1], box2.min_pt.e[1]);
  double min_z = std::min(box1.min_pt.e[2], box2.min_pt.e[2]);

  double max_x = std::max(box1.max_pt.e[0], box2.max_pt.e[0]);
  double max_y = std::max(box1.max_pt.e[1], box2.max_pt.e[1]);
  double max_z = std::max(box1.max_pt.e[2], box2.max_pt.e[2]);

  this->x_domain = interval(min_x, max_x);
  this->y_domain = interval(min_y, max_y);
  this->z_domain = interval(min_z, max_z);

  this->min_pt = point(min_x, min_y, min_z);
  this->max_pt = point(max_x, max_y, max_z);
}

bounding_box::bounding_box(){
  
}

void bounding_box::padding_minimums(){
  bool need_update = false;
  if (this->x_domain.size()<NEAR_ZERO_BUF){
    this->x_domain.expand(NEAR_ZERO_BUF);
    need_update=true;
  }
  if (this->y_domain.size()<NEAR_ZERO_BUF){
    this->y_domain.expand(NEAR_ZERO_BUF);
    need_update=true;
  }
  if (this->z_domain.size()<NEAR_ZERO_BUF){
    this->z_domain.expand(NEAR_ZERO_BUF);
    need_update=true;
  }
  if (need_update){
    this->min_pt = point(this->x_domain.min, this->y_domain.min, this->z_domain.min);
    this->max_pt = point(this->x_domain.max, this->y_domain.max, this->z_domain.max);
  }
}

bool bounding_box::hit(const ray& r) const {
  // The algorithm from https://gamedev.stackexchange.com/questions/18436/most-efficient-aabb-vs-ray-collision-algorithms
  // Key point float/0 no exception
  // To min pt the max factor larger than max pt min factor it would not hit
  // Here we go 

  float dfrac_x = 1.0f/r.direction().x();
  float dfrac_y = 1.0f/r.direction().y();
  float dfrac_z = 1.0f/r.direction().z();

  float x_fact_min = (this->min_pt.x() - r.origin().x())*dfrac_x;
  float y_fact_min = (this->min_pt.y() - r.origin().y())*dfrac_y;
  float z_fact_min = (this->min_pt.z() - r.origin().z())*dfrac_z;

  float x_fact_max = (this->max_pt.x() - r.origin().x())*dfrac_x;
  float y_fact_max = (this->max_pt.y() - r.origin().y())*dfrac_y;
  float z_fact_max = (this->max_pt.z() - r.origin().z())*dfrac_z;

  float fact_min = std::max(std::max(std::min(x_fact_min,x_fact_max), std::min(y_fact_min,y_fact_max)), std::min(z_fact_min, z_fact_max));
  float fact_max = std::min(std::min(std::max(x_fact_min,x_fact_max), std::max(y_fact_min,y_fact_max)), std::max(z_fact_min, z_fact_max));

  // if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
  if (fact_max < 0) {
    return false;
  }

  // if tmin > tmax, ray doesn't intersect AABB
  if (fact_min > fact_max) { 
    return false;
  }
  return true;
}

bool bounding_box::contains(const point& p){
  return this->x_domain.contains(p.e[0]) && this->y_domain.contains(p.e[1]) && this->z_domain.contains(p.e[2]);
}

axis bounding_box::longest_axis() const{
  if (this->x_domain.size() > this->y_domain.size() && this->x_domain.size() > this->z_domain.size()){
    return axis::X;    
  } else if (this->y_domain.size() > this->z_domain.size()){
    return axis::Y;
  } else {
    return axis::Z;
  }
}

interval bounding_box::axis_interval(axis ax) const {
  if (ax==axis::X){
    return this->x_domain;
  } else if (ax==axis::Y){
    return this->y_domain;
  } else {
    return this->z_domain;
  }
}
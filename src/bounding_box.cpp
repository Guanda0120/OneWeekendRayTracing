#include "bounding_box.h"

bounding_box::bounding_box(point pt1, point pt2){
  this->x_domain = interval(std::min(pt1.x(), pt2.x()), std::max(pt1.x(), pt2.x()));
  this->y_domain = interval(std::min(pt1.y(), pt2.y()), std::max(pt1.y(), pt2.y()));
  this->z_domain = interval(std::min(pt1.z(), pt2.z()), std::max(pt1.z(), pt2.z()));
  this->max_pt = point(this->x_domain.max, this->y_domain.max, this->z_domain.max);
  this->min_pt = point(this->x_domain.min, this->y_domain.min, this->z_domain.min);
}

bool bounding_box::hit(const ray& r){
  return true;
}
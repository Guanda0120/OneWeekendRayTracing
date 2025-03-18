#include "materials/gradiant.h"

gradiant::gradiant(color from, color to, string name) : from_c_(from), to_c_(to){
  this->name = name;
}

bool gradiant::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const{
  double ratio = 0.5* (r_in.direction().y() + 1.0);
  double neg_ratio = 1-ratio;
  attenuation = this->from_c_ * this->to_c_;
  // attenuation = color(
  //   (this->from_c_.r*neg_ratio+this->to_c_.r*ratio)/255.9,
  //   (this->from_c_.g*neg_ratio+this->to_c_.g*ratio)/255.9,
  //   (this->from_c_.b*neg_ratio+this->to_c_.b*ratio)/255.9
  // );
  return true;
}

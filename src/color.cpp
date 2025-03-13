#include "color.h"

color::color():r_(0),g_(0),b_(0){};

color::color(float r_ratio, float g_ratio, float b_ratio)
  : r_(r_ratio), g_(g_ratio), b_(b_ratio){};

int color::r() { return int(this->r_/color::__INT_COL_FACTOR__); }
int color::g() { return int(this->g_/color::__INT_COL_FACTOR__); }
int color::b() { return int(this->b_/color::__INT_COL_FACTOR__); }

void color::write_color(std::ostream& out){
  out<<this->r_<<' '<<this->g_<<' '<<this->b_<<'\n';
}

void color::garmmar_correction(double garmmar_coe){
  this->r_ = this->r_*garmmar_coe;
  this->g_ = this->g_*garmmar_coe;
  this->b_ = this->b_*garmmar_coe;
}

void color::garmmar_correction(){
  this->r_ = std::sqrt(this->r_);
  this->g_ = std::sqrt(this->g_);
  this->b_ = std::sqrt(this->b_);
}

color color::random(){
  return color(random_double(), random_double(), random_double());
}

color color::random(double min, double max){
  return color(random_double(min, max), random_double(min, max), random_double(min, max));
}
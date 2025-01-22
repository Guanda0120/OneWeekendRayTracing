#include "color.h"

color::color():r(0),g(0),b(0){};

color::color(double r_ratio, double g_ratio, double b_ratio){
  this->r = int(r_ratio * 255.999);
  this->g = int(g_ratio * 255.999);
  this->b = int(b_ratio * 255.999);
}

void color::write_color(std::ostream& out){
  out<<this->r<<' '<<this->g<<' '<<this->b<<'\n';
}

void color::garmmar_correction(double garmmar_coe){
  this->r = int(this->r*garmmar_coe);
  this->g = int(this->g*garmmar_coe);
  this->b = int(this->b*garmmar_coe);
}

void color::garmmar_correction(){
  this->r = int(std::sqrt(this->r/255.999)*255);
  this->g = int(std::sqrt(this->g/255.999)*255);
  this->b = int(std::sqrt(this->b/255.999)*255);
}

color color::random(){
  return color(random_double(), random_double(), random_double());
}

color color::random(double min, double max){
  return color(random_double(min, max), random_double(min, max), random_double(min, max));
}
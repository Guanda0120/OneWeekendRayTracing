#include "color.h"

color::color():r(0),g(0),b(0){};

color::color(float r_ratio, float g_ratio, float b_ratio)
  : r(r_ratio), g(g_ratio), b(b_ratio){};

int color::r_int() { return int(this->r*color::__INT_COL_FACTOR__); }
int color::g_int() { return int(this->g*color::__INT_COL_FACTOR__); }
int color::b_int() { return int(this->b*color::__INT_COL_FACTOR__); }

void color::write_color(std::ostream& out){
  out<<this->r<<' '<<this->g<<' '<<this->b<<'\n';
}

void color::garmmar_correction(double garmmar_coe){
  this->r = this->r*garmmar_coe;
  this->g = this->g*garmmar_coe;
  this->b = this->b*garmmar_coe;
}

void color::garmmar_correction(){
  this->r = std::sqrt(this->r);
  this->g = std::sqrt(this->g);
  this->b = std::sqrt(this->b);
}

color& color::operator+=(const color& col_2){
  this->r += col_2.r;
  this->g += col_2.g;
  this->b += col_2.b;
  return *this;
}

color& color::operator*=(const color& col_2){
  this->r *= col_2.r;
  this->g *= col_2.g;
  this->b *= col_2.b;
  return *this;
}

color& color::operator*=(const float factor){
  this->r *= factor;
  this->g *= factor;
  this->b *= factor;
  return *this;
}

color color::random(){
  return color(random_double(), random_double(), random_double());
}

color color::random(double min, double max){
  return color(random_double(min, max), random_double(min, max), random_double(min, max));
}
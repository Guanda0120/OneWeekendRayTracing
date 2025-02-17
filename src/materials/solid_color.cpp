#include "materials/solid_color.h"

solid_color::solid_color(const color& albedo): albedo_(albedo){}

solid_color::solid_color(double r, double g, double b): albedo_(color(r,g,b)){}

color solid_color::value(double u, double v, const point& p) const {
  return this->albedo_;
}
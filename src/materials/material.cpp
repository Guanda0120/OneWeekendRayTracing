#include "materials/material.h"


bool material::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
  return false;
}

color material::emitted(double u, double v, const point& p) const{
  return color(0,0,0);
}
#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <cmath>
#include "rt_constance.h"

class color{

  public:
    color();
    color(float r_ratio, float g_ratio, float b_ratio);
    void write_color(std::ostream& out);
    int r();
    int g();
    int b();
  
    const float __INT_COL_FACTOR__ = 255.99999f;
    void garmmar_correction(double garmmar_coe);
    void garmmar_correction();

    static color random();
    static color random(double min, double max);

  private:
    float r_;
    float g_;
    float b_;
  
};

inline color operator*(const color& col_1,const color& col_2){
  return color(
    (col_1.r_ * col_2.r)/(255.999*255.999),
    (col_1.g * col_2.g)/(255.999*255.999),
    (col_1.b * col_2.b)/(255.999*255.999)
  );
} 

#endif
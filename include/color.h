#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include <cmath>
#include "rt_constance.h"

class color{

  public:
    color();
    color(double r_ratio, double g_ratio, double b_ratio);
    void write_color(std::ostream& out);
    int r;
    int g;
    int b;
    
    void garmmar_correction(double garmmar_coe);
    void garmmar_correction();

    static color random();
    static color random(double min, double max);
};

inline color operator*(const color& col_1,const color& col_2){
  return color(
    (col_1.r * col_2.r)/(255.999*255.999),
    (col_1.g * col_2.g)/(255.999*255.999),
    (col_1.b * col_2.b)/(255.999*255.999)
  );
} 

#endif
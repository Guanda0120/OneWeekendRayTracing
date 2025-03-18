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
    int r_int();
    int g_int();
    int b_int();
  
    static constexpr float __INT_COL_FACTOR__ = 255.99999f;
    void garmmar_correction(double garmmar_coe);
    void garmmar_correction();

    color& operator+=(const color& col_2);
    color& operator*=(const color& col_2);
    color& operator*=(const float factor);

    static color random();
    static color random(double min, double max);

    float r;
    float g;
    float b;
  
};

/// @brief The Color filter, Use on Color lambert diffuse
/// @param col_1 
/// @param col_2 
/// @return 
inline color operator*(const color& col_1,const color& col_2){
  return color(
    col_1.r * col_2.r,
    col_1.g * col_2.g,
    col_1.b * col_2.b
  );
} 

/// @brief The Color add on method, Use in Color，Emit addition
/// @param col_1 
/// @param col_2 
/// @return 
inline color operator+(const color& col_1, const color& col_2){
  return color(
    col_1.r + col_2.r,
    col_1.g + col_2.g,
    col_1.b + col_2.b
  );  
}

inline color operator*(const color& col, double factor){
  return color(
    col.r * factor,
    col.g * factor,
    col.b * factor
  );
}

#endif
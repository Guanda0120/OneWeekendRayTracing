#ifndef COLOR
#define COLOR

#include<iostream>
#include<cmath>

class color{
  private:
    int r;
    int g;
    int b;
  
  public:
    color(double r_ratio, double g_ratio, double b_ratio);
    void wrtie_color(std::ostream& out);
};

#endif
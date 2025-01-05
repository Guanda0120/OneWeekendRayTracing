#ifndef COLOR_H
#define COLOR_H

#include<iostream>
#include<cmath>

class color{

  public:
    color();
    color(double r_ratio, double g_ratio, double b_ratio);
    void write_color(std::ostream& out);
    int r;
    int g;
    int b;

};

#endif
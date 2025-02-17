#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H

#include "texture.h"

class solid_color: public texture{
  
  public: 

    solid_color(const color& albedo);

    solid_color(double r, double g, double b);

    color value(double u, double v, const point& p) const override;

  private:
    color albedo_;

};

#endif
#ifndef TEXTURE_H
#define TEXTURE_H

#include "color.h"
#include "vec3.h"

class texture{
  public:
  
    virtual ~texture() = default;

    virtual color value(double u, double v, const point& p) const = 0;
};

#endif
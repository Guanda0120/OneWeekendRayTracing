#ifndef CANVAS_H
#define CANVAS_H

#include "vec3.h"

class canvas{
  public:

    canvas(int width, double aspect_ratio);

    int width;

    int height;

    double aspect_ratio;
};

#endif
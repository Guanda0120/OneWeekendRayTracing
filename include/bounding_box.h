#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "interval.h"
#include "ray.h"

class bounding_box{
  public:
    interval x, y, z;

    bounding_box();

    bool hit(const ray& r);

};

#endif 
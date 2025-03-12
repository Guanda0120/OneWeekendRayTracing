#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H

#include "materials/texture.h"
#include "materials/material.h"
#include "materials/solid_color.h"


class diffuse_light: public material{
  public: 
    diffuse_light(texture* tex);

    diffuse_light(const color color);

    ~diffuse_light();

    color emitted(double u, double v, const point& p) const override;
  
  private:
    texture* tex_;
};

#endif
#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

#include "materials/texture.h"
#include "image.h"

class image_texture: public texture{
  public:
    image_texture(const char* filename);
    color value(double u, double v, const point& p) const override;
    ~image_texture();
  private:
    image* image_;
};

#endif
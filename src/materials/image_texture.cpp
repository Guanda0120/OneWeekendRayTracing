#include "materials/image_texture.h"


image_texture::image_texture(const char* filename){
  this->image_ = new image(filename);
}

image_texture::~image_texture(){
  delete this->image_;
}

color image_texture::value(double u, double v, const point& p) const{
  return this->image_->index_uv(u, v);
}
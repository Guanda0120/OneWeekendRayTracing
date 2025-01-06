#include "camera.h"

camera::camera(const canvas& canvas, const hittable& hit, double v_width, double far_plane_d):
  viewport_width_(v_width), far_plane_dist_(far_plane_d), entity_(hit)
{
  
  this->location_ = vec3(0.0,0.0,0.0);
  this->aspect_ratio_ = canvas.aspect_ratio;
  this->viewport_height_ = this->aspect_ratio_*this->viewport_width_;
  
  this->delta_width_ = this->viewport_width_/canvas.width;
  this->delta_height_ = this->viewport_height_/canvas.height;

  this->width_direction_ = vec3(1.0,0.0,0.0);
  this->height_direction_ = vec3(0.0,-1.0,0.0);

  this->pixel_width_ = canvas.width;
  this->pixel_height_ = canvas.height;

  this->start_pt_ = vec3(-this->viewport_width_/2, this->viewport_height_/2, this->far_plane_dist_);
};

image camera::render(){
  // Image on stack
  image img = image(this->pixel_width_, this->pixel_height_);
  
  for(int i=0; i<this->pixel_height_; i++){
    for(int j=0; j<this->pixel_width_; j++){
      
      // Compute distance
      vec3 tag_vec = this->start_pt_
        +(i*delta_height_)*this->height_direction_
        +(j*delta_width_)*this->width_direction_;
      vec3 direc_vec = tag_vec-this->location_;
      
      direc_vec.normalize_vec();

      // Compute Color
      double a = 0.5*(direc_vec.y() + 1.0);
      
      color c = color (
        (1.0-a)+0.5*a,
        (1.0-a)+0.7*a,
        (1.0-a)+1.0*a
      );
      //Add to Image
      img.insert_color(j, i, c);
    }
  }

  return img;
}

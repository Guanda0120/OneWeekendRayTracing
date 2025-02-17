#include "camera.h"

camera::camera(
  const canvas& canvas, 
  double fov,
  double far_plane_d,
  point origin, 
  vec3 look_at, 
  vec3 up_at
):
  fov_(fov), far_plane_dist_(far_plane_d), location_(origin), look_at_(look_at), up_at_(up_at) 
{
  // Camera Location
  this->aspect_ratio_ = canvas.aspect_ratio;
  this->viewport_width_ = std::tan(this->fov_/2)*this->far_plane_dist_*2;
  this->viewport_height_ = this->viewport_width_/this->aspect_ratio_;
  
  this->delta_width_ = this->viewport_width_/canvas.width;
  this->delta_height_ = this->viewport_height_/canvas.height;
  // this->delta_height_ = this->delta_width_;
  // TODO 
  this->height_direction_ = -vec3(this->up_at_);
  this->width_direction_ = cross(this->look_at_, this->up_at_);
  // this->width_direction_ = vec3(1.0,0.0,0.0);
  // this->height_direction_ = vec3(0.0,-1.0,0.0);

  this->pixel_width_ = canvas.width;
  this->pixel_height_ = canvas.height;
  // this->viewport_height_ = this->pixel_height_*this->delta_height_;

  this->sample_per_pixel_=10;
  this->sample_level_=3;

  this->max_depth_ = 10;
  this->gammar_coe_ = 0.5;

  this->start_pt_ = this->location_+this->far_plane_dist_*this->look_at_
    -(this->viewport_height_/2)*this->height_direction_
    -(this->viewport_width_/2)*this->width_direction_;

  this->shutter_open_ = 1.00;
  // this->start_pt_ = point(-this->viewport_width_/2, this->viewport_height_/2, -this->far_plane_dist_);
};

image camera::render(const hittable& entity){
  // Image on stack
  image img = image(this->pixel_width_, this->pixel_height_);
  
  for(int i=0; i<this->pixel_height_; i++){
    for(int j=0; j<this->pixel_width_; j++){
      // color c = this->random_ray_aliase(entities, i, j);
      color c = this->multi_sample_aliase(entity, i, j, this->sample_level_);
      c.garmmar_correction();
      img.insert_color(j, i, c);
    }
  }

  return img;
};

image camera::render(const hittable_list& entities){
  // Image on stack
  image img = image(this->pixel_width_, this->pixel_height_);
  
  for(int i=0; i<this->pixel_height_; i++){
    for(int j=0; j<this->pixel_width_; j++){
      // color c = this->random_ray_aliase(entities, i, j);
      color c = this->multi_sample_aliase(entities, i, j, this->sample_level_);
      c.garmmar_correction();
      img.insert_color(j, i, c);
    }
  }

  return img;
}

color camera::multi_sample_aliase(const hittable_list& entities, int i, int j, int sample_level) const {
  int r=0, g=0, b=0;
  int sample_pts = sample_level*sample_level;

  double i_step = this->delta_height_/sample_level;
  double j_step = this->delta_width_/sample_level;

  for (int m=0; m<sample_level;m++){
    for (int n=0; n<sample_level;n++){
      vec3 tag_pt = this->start_pt_
        +(i*this->delta_height_+i_step*m)*this->height_direction_
        +(j*this->delta_width_+j_step*n)*this->width_direction_;
        vec3 direc_vec = tag_pt-this->location_;
      direc_vec.normalize_vec();
      vec3 center = this->location_;
      // Consider Move object
      double tm = random_double(0, this->shutter_open_);
      ray tmp_ray = ray(center, direc_vec, tm);
      color tmp_color = this->cal_pixel_color_(entities, tmp_ray, this->max_depth_-1);
      r+=tmp_color.r;
      g+=tmp_color.g;
      b+=tmp_color.b;
    }
  }
  color c = color();
  c.r = int(r/sample_pts);
  c.g = int(g/sample_pts);
  c.b = int(b/sample_pts);
  return c;
}


color camera::multi_sample_aliase(const hittable& entity, int i, int j, int sample_level) const {
  int r=0, g=0, b=0;
  int sample_pts = sample_level*sample_level;

  double i_step = this->delta_height_/sample_level;
  double j_step = this->delta_width_/sample_level;

  for (int m=0; m<sample_level;m++){
    for (int n=0; n<sample_level;n++){
      vec3 tag_pt = this->start_pt_
        +(i*this->delta_height_+i_step*m)*this->height_direction_
        +(j*this->delta_width_+j_step*n)*this->width_direction_;
        vec3 direc_vec = tag_pt-this->location_;
      direc_vec.normalize_vec();
      vec3 center = this->location_;
      // Consider Move object
      double tm = random_double(0, this->shutter_open_);
      ray tmp_ray = ray(center, direc_vec, tm);
      color tmp_color = this->cal_pixel_color_(entity, tmp_ray, this->max_depth_ - 1);
      r+=tmp_color.r;
      g+=tmp_color.g;
      b+=tmp_color.b;
    }
  }
  color c = color();
  c.r = int(r/sample_pts);
  c.g = int(g/sample_pts);
  c.b = int(b/sample_pts);
  return c;
}

color camera::random_ray_aliase(const hittable_list& entities, int i, int j) const {
  int r=0, g=0, b=0;
  for (int k=0; k<this->sample_per_pixel_; k++){
    ray rand_ray = this->get_ray(i,j);
    color tmp_c = this->cal_pixel_color_(entities, rand_ray, this->max_depth_);
    r+=tmp_c.r;
    g+=tmp_c.g;
    b+=tmp_c.b;
  }
  color c = color();
  c.r = int(r/this->sample_per_pixel_);
  c.g = int(g/this->sample_per_pixel_);
  c.b = int(b/this->sample_per_pixel_);
  return c;
}

ray camera::get_ray(int i, int j) const {
  double i_d = i+random_double();
  double j_d = j+random_double();
  vec3 tag_vec = this->start_pt_
    +(i_d*delta_height_)*this->height_direction_
    +(j_d*delta_width_)*this->width_direction_;
  vec3 direc_vec = tag_vec-this->location_;
  direc_vec.normalize_vec();
  vec3 center = this->location_;
  return ray(center, direc_vec);
}

color camera::cal_pixel_color_(const hittable_list& entities, const ray& r, int depth) const {
  if (depth<=0){
    double a = 0.5 * (r.direction().y() + 1.0);
    return color(
        (1.0 - a) + 0.5 * a,
        (1.0 - a) + 0.7 * a,
        (1.0 - a) + 1.0 * a
    );
  }
  hit_record record;
  color c;
  if (entities.hit(r, interval(0, 1000), record)){
    // Get the Normalize Vector 
    /*
    vec3 sphere_normal = record.normal;
    c = color(0.5*(sphere_normal.x()+1), 0.5*(sphere_normal.y()+1), 0.5*(sphere_normal.z()+1));
    */
    color attenuation;
    ray scattered;
    /*
    vec3 sphere_normal = record.normal;
    vec3 rand_direc = random_unit_vector_hemisphere(sphere_normal);
    vec3 lambert_direc = rand_direc+sphere_normal;
    lambert_direc.normalize_vec();
    ray rand_ray = ray(record.p, lambert_direc);
    */
    // This recurancy Means
    /**
     * 
     * 
     *         o
     *          \  ________________
     *           \ |              |
     *  0.125sky  \| 0.5sky       |
     *         \  /|              |
     * _________\/_|______________|______________
     *         0.25sky 
     */ 
    if (record.mat->scatter(r, record, attenuation, scattered)){
      return attenuation*this->cal_pixel_color_(entities, scattered, depth-1);
    }
    // color c = this->cal_pixel_color_(entities, rand_ray, depth-1);
    // c.garmmar_correction(this->gammar_coe_);    
    return color(0,0,0);
  } else {
    // Not Hit just the blue gradient
    // Here is Environment Light
    double a = 0.5*(r.direction().y() + 1.0);    
    c = color (
      (1.0-a)+0.5*a,
      (1.0-a)+0.7*a,
      (1.0-a)+1.0*a
    );
  }
  return c;
}

color camera::cal_pixel_color_(const hittable& entity, const ray& r, int depth) const {
  if (depth<=0){
    double a = 0.5 * (r.direction().y() + 1.0);
    return color(
        (1.0 - a) + 0.5 * a,
        (1.0 - a) + 0.7 * a,
        (1.0 - a) + 1.0 * a
    );
  }
  hit_record record;
  color c;
  if (entity.hit(r, interval(0, 1000), record)){
    // Get the Normalize Vector 
    /*
    vec3 sphere_normal = record.normal;
    c = color(0.5*(sphere_normal.x()+1), 0.5*(sphere_normal.y()+1), 0.5*(sphere_normal.z()+1));
    */
    color attenuation;
    ray scattered;
    /*
    vec3 sphere_normal = record.normal;
    vec3 rand_direc = random_unit_vector_hemisphere(sphere_normal);
    vec3 lambert_direc = rand_direc+sphere_normal;
    lambert_direc.normalize_vec();
    ray rand_ray = ray(record.p, lambert_direc);
    */
    // This recurancy Means
    /**
     * 
     * 
     *         o
     *          \  ________________
     *           \ |              |
     *  0.125sky  \| 0.5sky       |
     *         \  /|              |
     * _________\/_|______________|______________
     *         0.25sky 
     */ 
    if (record.mat->scatter(r, record, attenuation, scattered)){
      return attenuation*this->cal_pixel_color_(entity, scattered, depth-1);
    }
    // color c = this->cal_pixel_color_(entities, rand_ray, depth-1);
    // c.garmmar_correction(this->gammar_coe_);    
    return color(0,0,0);
  } else {
    // Not Hit just the blue gradient
    // Here is Environment Light
    double a = 0.5*(r.direction().y() + 1.0);    
    c = color (
      (1.0-a)+0.5*a,
      (1.0-a)+0.7*a,
      (1.0-a)+1.0*a
    );
  }
  return c;
}
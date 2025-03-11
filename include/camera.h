#ifndef CAMERA_H
#define CAMERA_H

#include<iostream>
#include<cmath>
#include "canvas.h"
#include "image.h"
#include "hittable.h"
#include "hittable_list.h"
#include "rt_constance.h"
#include "ray.h"
#include "vec3.h"
#include "interval.h"
#include "materials/material.h"


class camera{
  public:
    camera(
      const canvas& canvas, 
      double fov, 
      double far_plane_d,
      point origin=point(0.0, 0.0, 0.0),
      vec3 look_at = vec3(0,0,-1),
      vec3 up_at = vec3(0,1,0)
    );
    ~camera();
    image render(const hittable& entity);
    image render(const hittable_list& entities);
    void set_bkg(material* mat);

  private:
    /// @brief Field of View, Tipically of horizontal
    double fov_;
    /// @brief The Loaction of camera
    vec3 location_;
    /// @brief The aspect ratio, pass from canvas
    double aspect_ratio_;
    /// @brief The Actual Width of viewport
    double viewport_width_;
    /// @brief the Actual Height if viewport
    double viewport_height_;
    /// @brief The far most viewport plane distance from camera loaction
    double far_plane_dist_;
    /// @brief The Step width for pixel of a viewport width
    double delta_width_;
    /// @brief The Step Height for pixel of a viewport height
    double delta_height_;
    /// @brief The ground true up left point coord
    point start_pt_;
    /// @brief Where is the Camera Look at
    vec3 look_at_;
    /// @brief Where is the UP direction at {unit vector}
    vec3 up_at_;
    /// @brief The width direction
    vec3 width_direction_;
    /// @brief The height direction
    vec3 height_direction_;
    /// @brief The Width pixel count
    int pixel_width_;
    /// @brief The Height pixel count
    int pixel_height_;
    /// @brief msaa param
    int sample_level_;
    /// @brief the scatter search depth.
    int max_depth_;
    /// @brief No Intersect color 
    material* background_;
    /// @brief Using MSAA Multi Sampling Anti Alias
    /// @param entities 
    /// @param i 
    /// @param j 
    /// @return 
    color multi_sample_aliase(const hittable_list& entities, int i, int j, int sample_level) const;
    
    /// @brief MSAA sample for single hittable
    /// @param entity 
    /// @param i 
    /// @param j 
    /// @param sample_level 
    /// @return 
    color multi_sample_aliase(const hittable& entity, int i, int j, int sample_level) const;
    
    /// @brief Just use random ray to alias the edge, with this-> sample_per_pixel_
    /// @param entities 
    /// @param i 
    /// @param j 
    /// @return 
    color random_ray_aliase(const hittable_list& entities, int i, int j) const;
    
    /// @brief Every pixel eject how much ray
    int sample_per_pixel_;
    /// @brief In for loop depends on i,j gives random shift ray
    /// @param i 
    /// @param j 
    /// @return a ray
    ray get_ray(int i, int j) const;
    
    /// @brief Cal
    /// @param entities 
    /// @param r 
    /// @param depth 
    /// @return 
    color cal_pixel_color_(const hittable_list& entities, const ray& r, int depth) const;
    
    /// @brief Render Single hitable
    /// @param entities The entities
    /// @param r ray
    /// @param depth  
    /// @return color for this pixel
    color cal_pixel_color_(const hittable& entity, const ray& r, int depth) const;
    
    /// @brief Gammar Coefficient
    double gammar_coe_;
    
    /// @brief The shutter open time
    double shutter_open_;
};

#endif
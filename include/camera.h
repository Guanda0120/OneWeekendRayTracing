#ifndef CAMERA_H
#define CAMERA_H

#include<iostream>
#include "canvas.h"
#include "image.h"
#include "hittable.h"
#include "hittable_list.h"
#include "rt_constance.h"


class camera{
  public:
    camera(const canvas& canvas, double v_width, double far_plane_d);
    image render(const hittable& entity);
    image render(const hittable_list& entities);

  private:
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
    vec3 start_pt_;
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
    /// @brief Using MSAA Multi Sampling Anti Alias
    /// @param entities 
    /// @param i 
    /// @param j 
    /// @return 
    color multi_sample_aliase(const hittable_list& entities, int i, int j, int sample_level) const;
    /// @brief 
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
    color cal_pixel_color_(const hittable_list& entities, const ray& r) const;
};

#endif
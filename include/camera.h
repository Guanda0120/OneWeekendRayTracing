#ifndef CAMERA_H
#define CAMERA_H

#include<iostream>
#include "vec3.h"
#include "canvas.h"
#include "image.h"
#include "hittable.h"

class camera{
  public:
    camera(const canvas& canvas, const hittable& entity, double v_width, double far_plane_d);
    image render();
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
    /// @brief A hittable entity
    hittable& entity_;
};

#endif
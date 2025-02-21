#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <cmath>
#include "interval.h"
#include "ray.h"

class bounding_box{
  private:
    void padding_minimums();
  
  public:
    
    /// @brief The x, y, z domain 
    interval x_domain, y_domain, z_domain;

    /// @brief The min and max point for bounding box
    point min_pt, max_pt;

    /// @brief Construct a bounding box
    /// @param pt1 The first point, not the min or max point
    /// @param pt2 The Second Point, not the min or max point
    bounding_box(point pt1, point pt2);

    /// @brief Union two box
    /// @param box1 
    /// @param box2 
    bounding_box(const bounding_box& box1, const bounding_box& box2);

    /// @brief Default Bounding Box;
    bounding_box();

    /// @brief Is the ray hit the bounding box
    /// @param r The ray object
    /// @return true for hit
    bool hit(const ray& r) const;

    /// @brief Check the point is inside the bounding box
    /// @param p point to check 
    /// @return true for in 
    bool contains(const point& p);

    /// @brief Get the longest axis
    /// @return 
    axis longest_axis()  const;
    
    interval axis_interval(axis ax) const;
};

#endif 
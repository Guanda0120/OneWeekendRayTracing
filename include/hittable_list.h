#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include <vector>
#include <memory>

#include "hittable.h"

class hittable_list{
  public:
    /// @brief Contaioner
    std::vector<std::shared_ptr<hittable>> objects;

    /// @brief Construct a
    hittable_list();

    /// @brief add objects to world 
    /// @param hittable_obj 
    void add(std::shared_ptr<hittable> hittable_obj);

    /// @brief Clear all the object
    void clear();

    /// @brief Loop over all the objects and check if it is intersect with every object
    /// @param r ray object
    /// @param ray_tmin tmin
    /// @param ray_tmax tmax
    /// @param rec 
    /// @return true for hit
    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const ;
};

#endif
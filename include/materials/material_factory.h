#ifndef MATERIAL_FACTORY_H
#define MATERIAL_FACTORY_H

#include <unordered_map>
#include <string>
#include "materials/material.h"
#include "materials/lambertian.h"
#include "materials/metal.h"
#include "materials/dielectric.h"


using std::unordered_map;
using std::string;

class material_factory{
  public:
    /// @brief Constructor of factory
    material_factory();
    /// @brief Get the material by name, if not found then return black lambert material
    /// @param mat_name The Search string 
    /// @return A ptr for material
    material* get_material(string mat_name);
    /// @brief Add a material to factory
    /// @param mat 
    void add_material(material* mat);
    /// @brief Delete all the material 
    ~material_factory();

  private:
    /// @brief Store all the material
    unordered_map<string, material*> material_dict;
    /// @brief Default material
    material* default_mat;
};

#endif
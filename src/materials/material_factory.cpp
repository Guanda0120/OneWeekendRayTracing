#include "materials/material_factory.h"


material_factory::material_factory(){
  this->default_mat = new lambertian(color(0,0,0), "Black");
  this->material_dict = unordered_map<string, material*>();
}

void material_factory::add_material(material* mat){
  this->material_dict[mat->name] = mat;
}

material* material_factory::get_material(string mat_name) {
  auto it = this->material_dict.find(mat_name);
  if (it != this->material_dict.end()) {
    return it->second;
  } else {
    return this->default_mat;
  }
}

material_factory::~material_factory(){
  for (auto& pair : this->material_dict) {
    delete pair.second;
  }
  delete this->default_mat;
}
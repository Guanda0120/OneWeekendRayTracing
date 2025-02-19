#include "materials/lambertian.h"

lambertian::lambertian(const color& albedo, string mat_name) {
  this->tex_ = new solid_color(albedo); 
  this->name = mat_name;
};

lambertian::lambertian(const color& odd, const color& even, double factor, string mat_name){
  this->tex_ = new checker_texture(factor, odd, even);
  this->name = mat_name;
}

lambertian::lambertian(const char* file_name, string mat_name){
  this->tex_ = new image_texture(file_name);
  this->name = mat_name;
}


lambertian::~lambertian(){
  delete this->tex_;
}

bool lambertian::scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const {
  auto scatter_direction = rec.normal + random_unit_vector_hemisphere(rec.normal);
  scatter_direction.normalize_vec();
  scattered = ray(rec.p, scatter_direction, r_in.time());
  attenuation = this->tex_->value(rec.u, rec.v, rec.p);
  return true;
};

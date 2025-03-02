#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "materials/material.h"
#include "materials/texture.h"
#include "materials/solid_color.h"
#include "materials/checker_texture.h"
#include "materials/image_texture.h"
#include "materials/perlin_texture.h"


class lambertian:public material {
  public:
    lambertian(const color& albedo, string mat_name);
    lambertian(const color& odd, const color& even, double factor, string mat_name);
    lambertian(const char* img_file, string mat_name);
    lambertian(double scale, string mat_name);
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const override;
    ~lambertian();
  private:
    texture* tex_;
    // color albedo_;
};

#endif
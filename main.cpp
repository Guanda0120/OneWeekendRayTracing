#include<iostream>
#include<memory>
#include<cmath>
#include <chrono>
#include "vec3.h"
#include "color.h"
#include "image.h"
#include "canvas.h"
#include "camera.h"
#include "sphere.h"
#include "hittable_list.h"
#include "materials/material_factory.h"
#include "bvh_node.h"

hittable_list generate_scene(){
  hittable_list world;

  lambertian* ground_material = new lambertian(color(0.5, 0.5, 0.5), "Ground");
  world.add(make_shared<sphere>(point(0,-1000,0), 1000, ground_material));
  for (int a = -11; a < 11; a++) {
      for (int b = -11; b < 11; b++) {
          auto choose_mat = random_double();
          point center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());
          if ((center - point(4, 0.2, 0)).length() > 0.9) {
              material* sphere_material;
              if (choose_mat < 0.8) {
                  // diffuse
                  auto albedo = color::random() * color::random();
                  sphere_material = new lambertian(albedo, "Mat");
                  auto center2 = center + vec3(0, random_double(0,.5), 0);
                  world.add(make_shared<sphere>(center, center2, 0.2, sphere_material));
              } else if (choose_mat < 0.95) {
                  // metal
                  auto albedo = color::random(0.5, 1);
                  auto fuzz = random_double(0, 0.5);
                  sphere_material = new metal(albedo, "mat", fuzz);
                  world.add(make_shared<sphere>(center, 0.2, sphere_material));
              } else {
                  // glass
                  sphere_material = new dielectric(1.5, "mat");
                  world.add(make_shared<sphere>(center, 0.2, sphere_material));
              }
          }
      }
  }
  auto material1 = new dielectric(1.5, "mat");
  world.add(make_shared<sphere>(point(0, 1, 0), 1.0, material1));
  auto material2 = new lambertian(color(0.4, 0.2, 0.1), "mat");
  world.add(make_shared<sphere>(point(-4, 1, 0), 1.0, material2));
  auto material3 = new metal(color(0.7, 0.6, 0.5), "Mat", 0.0);
  world.add(make_shared<sphere>(point(4, 1, 0), 1.0, material3));
  return world;
}

int main(){
  auto start = std::chrono::high_resolution_clock::now();
  // Canvas
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 240;
  canvas cav = canvas(image_width, aspect_ratio);
  
  // initial the material
  material_factory mat_factory = material_factory();
  
  lambertian* core_lambert = new lambertian(color(0.1, 0.2, 0.4), "DarkBlue"); 
  lambertian* ground_lambert = new lambertian(color(0.8, 0.8, 0.2), "Green");
  metal* left_mat = new metal(color(0.8, 0.8, 0.8),"Steel");
  // metal* right_mat = new metal(color(0.8, 0.6, 0.4),"Corn", 0.3);
  dielectric* right_mat = new dielectric(1/1.333, "Glass");
  mat_factory.add_material(core_lambert);
  mat_factory.add_material(ground_lambert);
  mat_factory.add_material(left_mat);
  mat_factory.add_material(right_mat);

  // Add a sphere to render
  // hittable_list world = hittable_list();
  // auto render_ball =std::make_shared<sphere>(point(0.0,0.0,-4.0), 0.3, core_lambert);  
  // world.add(render_ball);
  // auto ground_ball = std::make_shared<sphere>(point(0.0,-100.3,-4.0), 100.0, ground_lambert);
  // world.add(ground_ball);
  // auto left_ball = std::make_shared<sphere>(point(-0.62,0.0,-4.0), 0.3, left_mat);
  // world.add(left_ball);
  // auto right_ball = std::make_shared<sphere>(point(0.62,0.0,-4.0), 0.3, right_mat);
  // world.add(right_ball);
  
  hittable_list world = generate_scene();
  bvh_node node = bvh_node(world);
  // Camera
  point p = point(13,2,3);
  vec3 look_at= point(0,0,0)-p;
  look_at.normalize_vec();
  vec3 up_to = vec3(0,1,0);
  camera cam = camera(cav, pi*35/180, 100.0, p, look_at, up_to);
  cam.render(node);
  image img = cam.render(world);
  // const char* file_name = "C://Users/12748/Desktop/Learning/OneWeekendRayTracing/img/MotionBlur.png";
  const char* file_name = "D://OneWeekendRayTracing/img/BVH_Scene_Huge.png";
  img.save_png(file_name);
  std::cout<<"Write Successful!"<<std::endl;
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
};
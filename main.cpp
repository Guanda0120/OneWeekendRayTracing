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
#include "quad.h"
#include "hittable_list.h"
#include "materials/material_factory.h"
#include "materials/checker_texture.h"
#include "bvh_node.h"

hittable_list generate_scene(){
  hittable_list world;
  // lambertian* ground_material = new lambertian(color(0.5, 0.5, 0.5), "Ground");
  lambertian* ground_material = new lambertian(color(.2, .3, .1), color(.9, .9, .9), 0.32, "Checker");
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
  const char* texture_file = "D://OneWeekendRayTracing/img/earthmap1.png";
  lambertian* m = new lambertian(texture_file, "earth");
  world.add(make_shared<sphere>(point(4, 1, 0), 1.0, m));
  return world;
}

void bouncing_spheres(){
  // Canvas
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 1200;
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
  image img = cam.render(node);
  // const char* file_name = "C://Users/12748/Desktop/Learning/OneWeekendRayTracing/img/MotionBlur.png";
  const char* file_name = "D://OneWeekendRayTracing/img/Checker.png";
  img.save_png(file_name);
}

void checker_spheres(){

  double aspect_ratio = 16.0 / 9.0;
  int image_width = 1000;
  canvas cav = canvas(image_width, aspect_ratio);

  hittable_list world;
  lambertian* m = new lambertian(4, "checker");
  world.add(make_shared<sphere>(point(0,-1000, 0), 1000, m));
  world.add(make_shared<sphere>(point(0, 2, 0), 2, m));
  bvh_node node = bvh_node(world);
  
  // Camera
  point p = point(13,2,3);
  vec3 look_at= point(0,0,0)-p;
  look_at.normalize_vec();
  vec3 up_to = vec3(0,1,0);
  camera cam = camera(cav, pi*35/180, 100.0, p, look_at, up_to);

  image img = cam.render(node);
  const char* file_dir = "C://Users/12748/Desktop/Learning/OneWeekendRayTracing/img/Perlin.png";
  img.save_png(file_dir);
}

void earth_sphere(){
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 1200;
  canvas cav = canvas(image_width, aspect_ratio);

  hittable_list world;
  const char* texture_file = "D://OneWeekendRayTracing/img/earthmap.png";
  lambertian* m = new lambertian(texture_file, "earth");

  world.add(make_shared<sphere>(point(0,0, 0), 2, m));
  bvh_node node = bvh_node(world);
  
  // Camera
  point p = point(0,0,12);
  vec3 look_at= point(0,0,0)-p;
  look_at.normalize_vec();
  vec3 up_to = vec3(0,1,0);
  camera cam = camera(cav, pi*35/180, 100.0, p, look_at, up_to);

  image img = cam.render(node);
  const char* file_dir = "D://OneWeekendRayTracing/img/Earth.png";
  img.save_png(file_dir);
}

void quad_render(){
  hittable_list world;
  // Canvas
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 1000;
  canvas cav = canvas(image_width, aspect_ratio);
  // Materials
  auto left_red     = new lambertian(color(1.0, 0.2, 0.2), "red");
  auto back_green   = new lambertian(color(0.2, 1.0, 0.2), "green");
  auto right_blue   = new lambertian(color(0.2, 0.2, 1.0), "blue");
  auto upper_orange = new lambertian(color(1.0, 0.5, 0.0), "orange");
  auto lower_teal   = new lambertian(color(0.2, 0.8, 0.8), "teal");
  // Quads
  world.add(make_shared<quad>(point(-3,-2, 5), vec3(0, 0,-4), vec3(0, 4, 0), left_red));
  world.add(make_shared<quad>(point(-2,-2, 0), vec3(4, 0, 0), vec3(0, 4, 0), back_green));
  world.add(make_shared<quad>(point( 3,-2, 1), vec3(0, 0, 4), vec3(0, 4, 0), right_blue));
  world.add(make_shared<quad>(point(-2, 3, 1), vec3(4, 0, 0), vec3(0, 0, 4), upper_orange));
  world.add(make_shared<quad>(point(-2,-3, 5), vec3(4, 0, 0), vec3(0, 0,-4), lower_teal));
  bvh_node node = bvh_node(world);
  // Camera
  point p = point(0,0,9);
  vec3 look_at= point(0,0,0)-p;
  look_at.normalize_vec();
  vec3 up_to = vec3(0,1,0);
  camera cam = camera(cav, pi*80/180, 100.0, p, look_at, up_to);

  image img = cam.render(node);
  const char* file_name = "C://Users/12748/Desktop/Learning/OneWeekendRayTracing/img/Quad.png";
  // const char* file_name = "D://OneWeekendRayTracing/img/iii.png";
  img.save_png(file_name);
}

void TEST_QUAD(){
  auto left_red     = new lambertian(color(1.0, 0.2, 0.2), "red");
  quad q = quad(point(-3,-2, 5), vec3(0, 0,-4), vec3(0, 4, 0), left_red);
  ray r = ray( point(0,0,9), vec3(-3,0,3)-vec3(0,0,9));
  hit_record rec;
  bool hit_or_not = q.hit(r, interval(0,1000),rec);
  std::cout<<hit_or_not<<std::endl;
}

int main(){
  auto start = std::chrono::high_resolution_clock::now();
  // bouncing_spheres();
  // quad_render();
  checker_spheres();
  // TEST_QUAD();
  std::cout<<"Write Successful!"<<std::endl;
  auto end = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double> elapsed = end - start;
  std::cout << "Elapsed time: " << elapsed.count() << " seconds" << std::endl;
};
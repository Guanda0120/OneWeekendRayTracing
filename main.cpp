#include<iostream>
#include<memory>
#include<cmath>
#include "vec3.h"
#include "color.h"
#include "image.h"
#include "canvas.h"
#include "camera.h"
#include "sphere.h"
#include "hittable_list.h"
#include "materials/lambertian.h"
#include "materials/metal.h"

int main(){
  
  // Canvas
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 2400;
  canvas cav = canvas(image_width, aspect_ratio);
  
  // initial the material
  std::shared_ptr<lambertian> core_lambert = make_shared<lambertian>(color(0.1, 0.2, 0.4)); 
  std::shared_ptr<lambertian> ground_lambert = make_shared<lambertian>(color(0.8, 0.8, 0.2));
  std::shared_ptr<metal> left_mat = make_shared<metal>(color(0.8, 0.8, 0.8));
  std::shared_ptr<metal> right_mat = make_shared<metal>(color(0.8, 0.6, 0.4), 0.3);

  // Add a sphere to render
  hittable_list world = hittable_list();
  auto render_ball =std::make_shared<sphere>(point(0.0,0.0,-4.0), 0.3, core_lambert);  
  world.add(render_ball);
  auto ground_ball = std::make_shared<sphere>(point(0.0,-100.3,-4.0), 100.0, ground_lambert);
  world.add(ground_ball);
  auto left_ball = std::make_shared<sphere>(point(-0.7,0.0,-4.0), 0.3, left_mat);
  world.add(left_ball);
  auto right_ball = std::make_shared<sphere>(point(0.7,0.0,-4.0), 0.3, right_mat);
  world.add(right_ball);

  // Camera
  camera cam = camera(cav, pi*35/180, 5.0);
  image img = cam.render(world);
  // const char* file_name = "C://Users/12748/Desktop/Learning/OneWeekendRayTracing/img/Lambert1.png";
  const char* file_name = "D://OneWeekendRayTracing/img/Metal.png";
  img.save_png(file_name);
  std::cout<<"Write Successful!"<<std::endl;
};
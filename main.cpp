#include<iostream>
#include<memory>
#include "vec3.h"
#include "color.h"
#include "image.h"
#include "canvas.h"
#include "camera.h"
#include "sphere.h"
#include "hittable_list.h"
#include "materials/lambertian.h"

int main(){
  
  // Canvas
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 2400;
  canvas cav = canvas(image_width, aspect_ratio);
  
  // initial the material
  std::shared_ptr<lambertian> mat_lambert;
  std::shared_ptr<lambertian> mat_lambert;

  // Add a sphere to render
  hittable_list world = hittable_list();
  auto render_ball =std::make_shared<sphere>(point(0.0,0.0,-1.0), 0.3);  
  world.add(render_ball);
  auto ground_ball = std::make_shared<sphere>(point(0.0,-100.3,-1.0), 100.0);
  world.add(ground_ball);

  // Camera
  camera cam = camera(cav, 2.0, 1.0);
  image img = cam.render(world);
  // const char* file_name = "C://Users/12748/Desktop/Learning/OneWeekendRayTracing/Lambert.png";
  const char* file_name = "D://OneWeekendRayTracing/Lambert.png";
  img.save_png(file_name);
  std::cout<<"Write Successful!"<<std::endl;
};
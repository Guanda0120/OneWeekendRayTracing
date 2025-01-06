#include<iostream>
#include "vec3.h"
#include "color.h"
#include "image.h"
#include "canvas.h"
#include "camera.h"
#include "sphere.h"

int main(){
  
  // Canvas
  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  canvas cav = canvas(image_width, aspect_ratio);
  // Add a sphere to render
  point center = point(0.0,0.0,-1.0);
  sphere s = sphere(0.5, center);
  // Camera
  camera cam = camera(cav, 2.0, 1.0);
  image img = cam.render();
  const char* file_name = "D://OneWeekendRayTracing//1.png";
  img.save_png(file_name);
  
}
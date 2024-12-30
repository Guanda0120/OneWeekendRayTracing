#include<iostream>
#include "vec3.h"
#include "color.h"

int main(){
  // std::cout<<"HelloWorld"<<std::endl;  
   // Image
  int image_width = 256;
  int image_height = 256;
  // Render
  // The header for .ppm file 
  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
  for (int j = 0; j < image_height; j++) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;  
    for (int i = 0; i < image_width; i++) {
      
      color c = color(0.0, double(i)/(image_width-1), double(j)/(image_height-1));
      c.wrtie_color(std::cout);
    }
  }
  std::clog<< "\rDone.            \n";
}

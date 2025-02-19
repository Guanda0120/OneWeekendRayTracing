#ifndef IMAGE_H
#define IMAGE_H

#include "color.h"
#include <png.h>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>

class image{
  public:
    image(int width, int height);
    image(const char* file_name);
    ~image();
    void insert_color(int width, int height, color c);
    void save_png(const char* file_name);
    color index_uv(double u, double v) const;
  private:
    color* image_;
    int width_;
    int height_;
};

#endif
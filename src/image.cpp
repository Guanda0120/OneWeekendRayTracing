#include "image.h"


image::image(int width, int height):width_(width), height_(height){
  this->image_ = new color[this->height_*this->width_];
}

image::~image(){
  delete[] this->image_;
}

void image::insert_color(int width, int height, color color){
  this->image_[width+height*this->width_] = color;
}

void image::save_png(const char* file_name){
  // Open File
  FILE* fp = fopen(file_name, "wb");
  if (!fp) {
    perror("File open failed");
    return;
  }
  // Cosntruct Struct of png
  png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (!png) {
    fclose(fp);
    return;
  }

  png_infop info = png_create_info_struct(png);
  if (!info) {
    png_destroy_write_struct(&png, nullptr);
    fclose(fp);
    return;
  }

  if (setjmp(png_jmpbuf(png))) {
    png_destroy_write_struct(&png, &info);
    fclose(fp);
    return;
  }

  png_init_io(png, fp);
  png_set_IHDR(
    png, info, this->width_, this->height_,
    8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT
  );
  png_write_info(png, info);

  // Write png
  unsigned char* buffer = new unsigned char[width_ * height_ * 3];

  for (int y = 0; y < height_; ++y) {
    for (int x = 0; x < width_; ++x) {
      int index = y * width_ + x;
      color c = image_[index];
      
      // 将 color 对象的 RGB 分量存储到 buffer 中
      buffer[(y * width_ + x) * 3 + 0] = c.r;  // Red
      buffer[(y * width_ + x) * 3 + 1] = c.g;  // Green
      buffer[(y * width_ + x) * 3 + 2] = c.b;  // Blue
    }
  }
  for (int y = 0; y < height_; ++y) {
    png_write_row(png, buffer + y * width_ * 3);
  }

  png_write_end(png, nullptr);
  png_destroy_write_struct(&png, &info);
  fclose(fp);
  delete[] buffer;
}
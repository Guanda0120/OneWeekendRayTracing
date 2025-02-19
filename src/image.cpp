#include "image.h"


image::image(int width, int height):width_(width), height_(height){
  this->image_ = new color[this->height_*this->width_];
}

image::image(const char* file_name){
  FILE *fp = fopen(file_name, "rb");
  if (!fp) {
      throw std::runtime_error("Failed to open PNG file.");
  }

  // 读取 PNG 文件头信息
  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
      fclose(fp);
      throw std::runtime_error("Failed to create PNG read struct.");
  }

  png_infop info = png_create_info_struct(png);
  if (!info) {
      png_destroy_read_struct(&png, NULL, NULL);
      fclose(fp);
      throw std::runtime_error("Failed to create PNG info struct.");
  }

  if (setjmp(png_jmpbuf(png))) {
      png_destroy_read_struct(&png, &info, NULL);
      fclose(fp);
      throw std::runtime_error("PNG read error.");
  }

  png_init_io(png, fp);
  png_read_info(png, info);

  width_ = png_get_image_width(png, info);
  height_ = png_get_image_height(png, info);
  int bit_depth = png_get_bit_depth(png, info);
  int color_type = png_get_color_type(png, info);

  // 仅支持 RGB 或 RGBA
  if (color_type != PNG_COLOR_TYPE_RGB && color_type != PNG_COLOR_TYPE_RGBA) {
      png_destroy_read_struct(&png, &info, NULL);
      fclose(fp);
      throw std::runtime_error("Unsupported PNG color type.");
  }
  std::cout<<sizeof(color)<<std::endl;
  // 设定适当的色深
  if (bit_depth == 16) {
    png_set_strip_16(png);
  }

  png_read_update_info(png, info);

  // 为 image_ 分配内存
  image_ = new color[width_ * height_];

  // 读取图像数据
  png_bytep* rows = new png_bytep[height_];
  for (int y = 0; y < height_; ++y) {
    rows[y] = (png_bytep)(image_ + y * width_);
  }

  png_read_image(png, rows);

  delete[] rows;

  png_destroy_read_struct(&png, &info, NULL);
  fclose(fp);
}

color image::index_uv(double u, double v) const {
  size_t v_idx = size_t(std::floor(v/this->height_));
  size_t u_idx = size_t(std::floor(u/this->width_));
  return this->image_[v_idx*this->width_+u_idx];
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
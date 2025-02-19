#include "image.h"


image::image(int width, int height):width_(width), height_(height){
  this->image_ = new color[this->height_*this->width_];
}

image::image(const char* file_name){
  FILE* fp = fopen(file_name, "rb");
  if (!fp) {
      throw std::runtime_error("Failed to open PNG file.");
  }

  // 创建PNG读取结构体
  png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  if (!png) {
      fclose(fp);
      throw std::runtime_error("Failed to create PNG read struct.");
  }

  // 创建PNG信息结构体
  png_infop info = png_create_info_struct(png);
  if (!info) {
      png_destroy_read_struct(&png, NULL, NULL);
      fclose(fp);
      throw std::runtime_error("Failed to create PNG info struct.");
  }

  // 错误处理
  if (setjmp(png_jmpbuf(png))) {
      png_destroy_read_struct(&png, &info, NULL);
      fclose(fp);
      throw std::runtime_error("PNG reading error.");
  }

  png_init_io(png, fp);

  // 读取PNG文件头部信息
  png_read_info(png, info);

  // 获取图像宽度，高度和颜色类型等
  width_ = png_get_image_width(png, info);
  height_ = png_get_image_height(png, info);
  int color_type = png_get_color_type(png, info);
  int bit_depth = png_get_bit_depth(png, info);

  // 确保我们只处理RGB或者RGBA图像
  if (color_type != PNG_COLOR_TYPE_RGB && color_type != PNG_COLOR_TYPE_RGBA) {
      png_destroy_read_struct(&png, &info, NULL);
      fclose(fp);
      throw std::runtime_error("Only RGB or RGBA images are supported.");
  }

  // 如果图像是16位深度，转换为8位深度
  if (bit_depth == 16) {
      png_set_strip_16(png);
  }

  // 读取图像数据
  png_read_update_info(png, info);

  // 分配内存来存储图像数据
  std::vector<png_bytep> row_pointers(height_);
  for (int y = 0; y < height_; y++) {
      row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png, info));
  }

  // 读取图像的每一行数据
  png_read_image(png, row_pointers.data());

  // 初始化image_数组
  this->image_ = new color[width_ * height_];

  // 将图像数据转换为color对象
  for (int y = 0; y < height_; ++y) {
      for (int x = 0; x < width_; ++x) {
          // 如果是RGBA格式，加入Alpha通道
        if (color_type == PNG_COLOR_TYPE_RGBA) {
          png_bytep px_alpha = &(row_pointers[y][x * 4]);  // 每个像素有4个通道
          double r = px_alpha[0] / 255.0;  // Red
          double g = px_alpha[1] / 255.0;  // Green
          double b = px_alpha[2] / 255.0;  // Blue
          double a = px_alpha[3] / 255.0;  // Alpha
        
          // 将图像数据存储为color对象
          this->image_[y * width_ + x] = color(r, g, b);  // 假设color类支持Alpha通道
        } else {
          // 如果是RGB格式，不处理Alpha
          png_bytep px = &(row_pointers[y][x * 3]);  // 每个像素有3个通道
          double r = px[0] / 255.0;
          double g = px[1] / 255.0;
          double b = px[2] / 255.0;
        
          this->image_[y * width_ + x] = color(r, g, b);
        }
      }
  }

  // 释放内存
  for (int y = 0; y < height_; ++y) {
      free(row_pointers[y]);
  }

  png_destroy_read_struct(&png, &info, NULL);
  fclose(fp);
}

color image::index_uv(double u, double v) const {
  size_t v_idx = size_t(std::floor(v*(this->height_-1)));
  size_t u_idx = size_t(std::floor(u*(this->width_-1)));
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
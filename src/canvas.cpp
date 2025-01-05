#include "canvas.h"

canvas::canvas(int width, double aspect_ratio):
  width(width), aspect_ratio(aspect_ratio)
{
  this->height = int(this->width/this->aspect_ratio);
};
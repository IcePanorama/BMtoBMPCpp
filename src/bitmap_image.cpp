#include "bitmap_image.hpp"

#include <format>
#include <iostream>

BitmapImage::BitmapImage (uint32_t width, uint32_t height)
    : width_ (width), height_ (height)
{
  std::cout << std::format ("w: {:d}, h: {:d}\n", this->width_, this->height_);
}

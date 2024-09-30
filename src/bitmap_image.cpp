#include "bitmap_image.hpp"

#include <format>
#include <iostream>

BitmapImage::BitmapImage (uint32_t _width, uint32_t _height)
    : width (_width), height (_height)
{
  std::cout << std::format ("w: {:d}, h: {:d}\n", this->width, this->height);
}

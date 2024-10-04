#include "bitmap_image.hpp"

#include <cstdint>
#include <vector>

BitmapImage::BitmapImage (uint32_t width, uint32_t height)
    : width_ (width), height_ (height)
{
  this->data.emplace (this->height_, std::vector<uint8_t> (this->width_));
}

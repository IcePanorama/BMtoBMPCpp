#ifndef _BITMAP_IMAGE_HPP_
#define _BITMAP_IMAGE_HPP_

#include <cstdint>

class BitmapImage
{
  // std::string filename;
  uint32_t width_;
  uint32_t height_;
  // TODO: handle this part in a cpp kind of way
  // uint8_t **data;

public:
  BitmapImage (uint32_t width, uint32_t height);
};

#endif /* _BITMAP_IMAGE_HPP_ */

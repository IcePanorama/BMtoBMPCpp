#ifndef _BITMAP_IMAGE_HPP_
#define _BITMAP_IMAGE_HPP_

#include <cstdint>
#include <fstream>
#include <optional>
#include <vector>

class BitmapImage
{
  uint32_t width_;
  uint32_t height_;
  std::optional<std::vector<std::vector<uint8_t> > > data;

public:
  BitmapImage (uint32_t width, uint32_t height);

  void process_data (std::ifstream &bm_fptr, std::ifstream &pal_fptr);
};

#endif /* _BITMAP_IMAGE_HPP_ */

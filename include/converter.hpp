#ifndef _CONVERTER_HPP_
#define _CONVERTER_HPP_

#include "bitmap_image.hpp"

#include <fstream>
#include <optional>
#include <string>

class Converter
{
  std::ifstream bm_file;
  std::ifstream pal_file;
  std::optional<BitmapImage> output;

public:
  Converter (const std::string &bm_filename, const std::string &pal_filename,
             const std::string output_filename = "output.bmp");
};

#endif /* _CONVERTER_HPP_ */

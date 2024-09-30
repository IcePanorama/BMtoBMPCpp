#ifndef _CONVERTER_HPP_
#define _CONVERTER_HPP_

#include "bitmap_image.hpp"

#include <cstdint>
#include <fstream>
#include <optional>
#include <string>

class Converter
{
  std::ifstream bm_file;
  std::ifstream pal_file;
  std::string output_filename;
  std::optional<BitmapImage> output;

  std::ifstream load_file (const std::string &filename);
  uint32_t read_uint32_from_file (std::ifstream &fptr);

public:
  Converter (const std::string &bm_filename, const std::string &pal_filename,
             const std::string _output_filename = "output.bmp");
};

#endif /* _CONVERTER_HPP_ */

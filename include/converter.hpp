#ifndef _CONVERTER_HPP_
#define _CONVERTER_HPP_

#include <fstream>
#include <string>

class Converter
{
  std::ifstream bm_file;
  std::ifstream pal_file;
  std::string output_filename;

  std::ifstream load_file (const std::string &filename);

public:
  Converter (std::string &bm_filename, std::string &pal_filename,
             std::string _output_filename = "output.bmp");
};

#endif /* _CONVERTER_HPP_ */

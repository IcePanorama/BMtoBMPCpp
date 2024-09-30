#ifndef _CONVERTER_HPP_
#define _CONVERTER_HPP_

#include <fstream>
#include <string>

class Converter
{
  std::ifstream bm_file;
  std::ifstream pal_file;
  std::string output_filename;

public:
  Converter (std::string &bm_filename, std::string &pal_filename);
  Converter (std::string &bm_filename, std::string &pal_filename,
             std::string &output_filename);
};

#endif /* _CONVERTER_HPP_ */

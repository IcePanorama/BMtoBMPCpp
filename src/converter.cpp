#include "converter.hpp"

#include <format>

Converter::Converter (std::string &bm_filename, std::string &pal_filename,
                      std::string _output_filename)
    : output_filename (_output_filename)
{
  try
    {
      this->bm_file = load_file (bm_filename);
      this->pal_file = load_file (pal_filename);
    }
  catch (std::runtime_error &e)
    {
      throw e;
    }
}

std::ifstream
Converter::load_file (const std::string &filename)
{
  std::ifstream file (filename, std::ios::binary);
  if (!file)
    {
      throw std::runtime_error (
          std::format ("Error opening file, {}.\n", filename));
    }
  return file;
}

#include "converter.hpp"

#include <array>
#include <format>
#include <iostream>
#include <stdexcept>

Converter::Converter (const std::string &bm_filename,
                      const std::string &pal_filename,
                      const std::string output_filename)
    : output_filename_ (output_filename)
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

  uint32_t width;
  uint32_t height;

  try
    {
      width = read_uint32_from_file (bm_file);
      height = read_uint32_from_file (bm_file);
    }
  catch (std::runtime_error &e)
    {
      throw e;
    }

  this->output.emplace (width, height);
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

uint32_t
Converter::read_uint32_from_file (std::ifstream &fptr)
{
  std::array<uint8_t, 4> bytes;
  fptr.read (reinterpret_cast<char *> (bytes.data ()), sizeof (bytes));
  if (!fptr)
    throw std::runtime_error ("Error reading from file.\n");

  return ((static_cast<uint32_t> (bytes[3]) << 24)
          | (static_cast<uint32_t> (bytes[2]) << 16)
          | (static_cast<uint32_t> (bytes[1]) << 8)
          | static_cast<uint32_t> (bytes[0]));
}

#include "utils.hpp"

#include <array>
#include <format>
#include <stdexcept>

void
write_string_to_file (std::ofstream &fptr, const std::string &s)
{
  if (s.empty ())
    throw std::invalid_argument ("Input string cannot be empty.\n");

  fptr.write (s.c_str (), s.length ());
  if (!fptr)
    throw std::runtime_error ("Error writing data to output file.\n");
}

std::ifstream
load_file (const std::string &filename)
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
read_uint32_from_file (std::ifstream &fptr)
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

void
write_le_int_to_file (std::ofstream &fptr, const uint32_t x)
{
  std::array<uint8_t, 4> bytes
      = { static_cast<uint8_t> (x & 0xFF),
          static_cast<uint8_t> ((x & 0xFF00) >> 8),
          static_cast<uint8_t> ((x & 0xFF0000) >> 16),
          static_cast<uint8_t> ((x & 0xFF000000) >> 24) };

  fptr.write (reinterpret_cast<char *> (bytes.data ()), sizeof (bytes));
  if (!fptr)
    throw std::runtime_error ("Error writing uint32 to file.\n");
}

void
write_le_int_to_file (std::ofstream &fptr, const uint16_t x)
{
  std::array<uint8_t, 2> bytes = { static_cast<uint8_t> (x & 0xFF),
                                   static_cast<uint8_t> ((x & 0xFF00) >> 8) };

  fptr.write (reinterpret_cast<char *> (bytes.data ()), sizeof (bytes));
  if (!fptr)
    throw std::runtime_error ("Error writing uint16 to file.\n");
}

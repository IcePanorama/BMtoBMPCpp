//  Copyright (C) 2024  IcePanorama
//
//  This file is part of BMtoBMPCpp.
//
//  BMtoBMPCpp is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by the
//  Free Software Foundation, either version 3 of the License, or (at your
//  option) any later version.
//  This program is distributed in the hope that it will be useful, but WITHOUT
//  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
//  more details.
//
//  You should have received a copy of the GNU General Public License along
//  with this program.  If not, see <https://www.gnu.org/licenses/>.
#include "utils.hpp"

#include <array>
#include <format>
#include <stdexcept>

void
write_string_to_file (std::ofstream &fptr, const std::string &s)
{
  if (s.empty ())
    throw std::runtime_error ("Input string cannot be empty.\n");

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

void
write_byte_to_file (std::ofstream &fptr, const uint8_t b)
{
  fptr.write (reinterpret_cast<const char *> (&b), sizeof (b));
  if (!fptr)
    throw std::runtime_error ("Error writing uint16 to file.\n");
}

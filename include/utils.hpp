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
#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <cstdint>
#include <fstream>
#include <string>

std::ifstream load_file (const std::string &filename);
uint32_t read_uint32_from_file (std::ifstream &fptr);
void write_string_to_file (std::ofstream &fptr, const std::string &s);
void write_le_int_to_file (std::ofstream &fptr, const uint32_t x);
void write_le_int_to_file (std::ofstream &fptr, const uint16_t x);
void write_byte_to_file (std::ofstream &fptr, const uint8_t b);

#endif /* _UTILS_HPP_ */

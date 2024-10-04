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
#ifndef _CONVERTER_HPP_
#define _CONVERTER_HPP_

#include "bitmap_image.hpp"

/** Converts BM image files to bitmap images using PAL files. */
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

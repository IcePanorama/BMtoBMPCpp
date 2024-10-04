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
#ifndef _BITMAP_IMAGE_HPP_
#define _BITMAP_IMAGE_HPP_

#include <cstdint>
#include <fstream>
#include <optional>
#include <string>
#include <vector>

class BitmapImage
{
  const std::string filename_;
  uint32_t width_;
  uint32_t height_;
  /** The image's RGB pixel data. */
  std::optional<std::vector<std::vector<uint8_t> > > data;

  /**
   *  @see:
   * https://en.wikipedia.org/wiki/BMP_file_format#DIB_header_(bitmap_information_header)
   */
  void populate_BITMAPINFOHEADER (std::ofstream &output_fptr) const;
  /** Writes its RGB pixel data to `output_fptr`. */
  void export_data (std::ofstream &output_fptr) const;

public:
  BitmapImage (const std::string &filename, uint32_t width, uint32_t height);

  /**
   *  Fills `data` with RGB values using the palette indicies found in
   *  `bm_fptr` and the associated RGB color values found in `pal_fptr`. The
   *  correlation between palette indicies (or offsets) and RGB values is a
   *  simple `i * 3` equation, where i = an index/offset.
   */
  void process_data (std::ifstream &bm_fptr, std::ifstream &pal_fptr);

  /**
   *  Creates the `filename_`.bmp image on disk. It creates a 24-bits-per-pixel
   *  bitmap image with a `BITMAPINFOHEADER` as its DIB header.
   */
  void export_image (void) const;
};

#endif /* _BITMAP_IMAGE_HPP_ */

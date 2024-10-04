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
#include "converter.hpp"
#include "utils.hpp"

#include <stdexcept>

Converter::Converter (const std::string &bm_filename,
                      const std::string &pal_filename,
                      const std::string output_filename)
{
  try
    {
      this->bm_file = load_file (bm_filename);
      this->pal_file = load_file (pal_filename);
    }
  catch (const std::runtime_error &e)
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
  catch (const std::runtime_error &e)
    {
      throw e;
    }

  this->output.emplace (output_filename, width, height);
  try
    {
      output->process_data (this->bm_file, this->pal_file);
      output->export_image ();
    }
  catch (const std::runtime_error &e)
    {
      throw e;
    }
}

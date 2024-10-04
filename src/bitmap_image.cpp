#include "bitmap_image.hpp"

#include <array>
#include <cstdint>
#include <stdexcept>
#include <vector>

static constexpr uint8_t BYTES_PER_PIXEL = 3; // 24 bits-per-pixel

BitmapImage::BitmapImage (uint32_t width, uint32_t height)
    : width_ (width), height_ (height)
{
  this->data.emplace (this->height_,
                      std::vector<uint8_t> (this->width_ * BYTES_PER_PIXEL));
}

void
BitmapImage::process_data (std::ifstream &bm_fptr, std::ifstream &pal_fptr)
{
  /* Ensure we're at the start of the pixel data. */
  bm_fptr.seekg (0xC);

  for (int32_t i = this->height_ - 1; i >= 0; i--)
    {
      for (uint32_t j = 0; j < this->width_; j++)
        {
          /* Read offset into pal_fptr. */
          uint8_t pal_offset;
          bm_fptr.read (reinterpret_cast<char *> (&pal_offset), 1);
          if (!bm_fptr)
            throw std::runtime_error ("Error reading data from BM file.\n");

          /*
           *  TODO: cache rgb values, check cache prior to searching from the
           *  pal file again.
           */
          /* Read rgb values from pal file. */
          pal_fptr.seekg (pal_offset * 0x3);
          std::array<uint8_t, 3> rgb_values;
          pal_fptr.read (reinterpret_cast<char *> (rgb_values.data ()), 3);
          if (!pal_fptr)
            throw std::runtime_error ("Error reading data from PAL file.\n");

          /* Convert rgb data to little endian form. */
          this->data->at (i).at (j * 3) = rgb_values[2];
          this->data->at (i).at (j * 3 + 1) = rgb_values[1];
          this->data->at (i).at (j * 3 + 2) = rgb_values[0];
        }
    }
}

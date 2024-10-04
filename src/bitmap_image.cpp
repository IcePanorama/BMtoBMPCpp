#include "bitmap_image.hpp"
#include "utils.hpp"

#include <array>
#include <format>
#include <stdexcept>
#include <unordered_map>
#include <utility>

static constexpr uint8_t BYTES_PER_PIXEL = 3; // 24 bits-per-pixel

BitmapImage::BitmapImage (const std::string &filename, uint32_t width,
                          uint32_t height)
    : filename_ (filename), width_ (width), height_ (height)
{
  this->data.emplace (this->height_,
                      std::vector<uint8_t> (this->width_ * BYTES_PER_PIXEL));
}

void
BitmapImage::process_data (std::ifstream &bm_fptr, std::ifstream &pal_fptr)
{
  std::unordered_map<uint8_t, std::array<uint8_t, 3> > rgb_cache;

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

          std::array<uint8_t, 3> rgb_values;

          auto got = rgb_cache.find (pal_offset);
          if (got == rgb_cache.end ())
            {
              /* Read rgb values from pal file. */
              pal_fptr.seekg (pal_offset * 0x3);
              pal_fptr.read (reinterpret_cast<char *> (rgb_values.data ()), 3);
              if (!pal_fptr)
                throw std::runtime_error (
                    "Error reading data from PAL file.\n");
              rgb_cache.insert (std::make_pair (pal_offset, rgb_values));
            }
          else
            {
              rgb_values = rgb_cache.at (pal_offset);
            }

          /* Convert rgb data to little endian form. */
          this->data->at (i).at (j * 3) = rgb_values[2];
          this->data->at (i).at (j * 3 + 1) = rgb_values[1];
          this->data->at (i).at (j * 3 + 2) = rgb_values[0];
        }
    }
}

void
BitmapImage::export_image (void) const
{
  std::ofstream fptr (this->filename_, std::ios::binary);
  if (!fptr)
    throw std::runtime_error (std::format (
        "Error opening file, {}, for output.\n", this->filename_));

  /* Ensure we're at the beginning of the file. */
  fptr.seekp (0x0);

  try
    {
      write_string_to_output_file (fptr, "BM");
    }
  catch (const std::exception &e)
    {
      throw e;
    }
}

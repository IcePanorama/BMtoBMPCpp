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
      populate_BITMAPINFOHEADER (fptr);
      export_data (fptr);

      /* Update size of pixel array in header. */
      size_t file_size = fptr.tellp ();
      fptr.seekp (0x22);
      write_le_int_to_file (fptr, static_cast<uint32_t> (file_size - 54));
    }
  catch (const std::exception &e)
    {
      throw e;
    }
}

void
BitmapImage::populate_BITMAPINFOHEADER (std::ofstream &output_fptr) const
{
  const uint32_t pixel_data_size
      = this->height_ * this->width_ * BYTES_PER_PIXEL;
  const uint32_t output_file_size = 54 + pixel_data_size;
  constexpr int32_t ppm_resolution = 0x0B13; // pixel per meter

  try
    {
      /* Populate BITMAPINFOHEADER. */
      write_string_to_file (output_fptr, "BM");
      write_le_int_to_file (output_fptr, output_file_size);
      write_le_int_to_file (output_fptr,
                            static_cast<uint32_t> (0x0)); // reserved
      // pixel array offset
      write_le_int_to_file (output_fptr, static_cast<uint32_t> (0x36));
      // DIB header size
      write_le_int_to_file (output_fptr, static_cast<uint32_t> (0x28));
      write_le_int_to_file (output_fptr, this->width_);  // DIB header size
      write_le_int_to_file (output_fptr, this->height_); // DIB header size
      // num color planes
      write_le_int_to_file (output_fptr, static_cast<uint16_t> (0x1));
      // bits per pixel
      write_le_int_to_file (output_fptr,
                            static_cast<uint16_t> (BYTES_PER_PIXEL * 8));
      // no compression
      write_le_int_to_file (output_fptr, static_cast<uint32_t> (0x0));
      /*
       *  img size, dummy 0x0 is okay for uncompressed images, which is what
       *  we're doing here.
       *  see:
       * https://en.wikipedia.org/wiki/BMP_file_format#DIB_header_(bitmap_information_header)
       */
      write_le_int_to_file (output_fptr, static_cast<uint32_t> (0x0));
      // horizontal resolution (in ppm)
      write_le_int_to_file (output_fptr,
                            static_cast<uint32_t> (ppm_resolution));
      // vertical resolution (in ppm)
      write_le_int_to_file (output_fptr,
                            static_cast<uint32_t> (ppm_resolution));
      // num colors in palette
      write_le_int_to_file (output_fptr, static_cast<uint32_t> (0x0));
      // num important colors
      write_le_int_to_file (output_fptr, static_cast<uint32_t> (0x0));
    }
  catch (const std::exception &e)
    {
      throw e;
    }
}

void
BitmapImage::export_data (std::ofstream &output_fptr) const
{
  const uint32_t pad = (4 - (this->width_ * BYTES_PER_PIXEL) % 4) % 4;
  for (uint32_t i = 0; i < this->height_; i++)
    {
      for (uint32_t j = 0; j < this->width_; j++)
        {
          for (uint8_t k = 0; k < BYTES_PER_PIXEL; k++)
            {
              write_byte_to_file (output_fptr, data->at (i).at (j * 3 + k));
            }
        }

      for (uint32_t p = 0; p < pad; p++)
        write_byte_to_file (output_fptr, 0x0);
    }
}

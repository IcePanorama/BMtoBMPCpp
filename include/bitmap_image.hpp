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
  std::optional<std::vector<std::vector<uint8_t> > > data;

  void write_string_to_output_file (std::ofstream &fptr,
                                    const std::string &s) const;

public:
  BitmapImage (const std::string &filename, uint32_t width, uint32_t height);

  void process_data (std::ifstream &bm_fptr, std::ifstream &pal_fptr);
  void export_image (void) const;
};

#endif /* _BITMAP_IMAGE_HPP_ */

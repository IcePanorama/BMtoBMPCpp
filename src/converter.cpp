#include "converter.hpp"
#include "utils.hpp"

Converter::Converter (const std::string &bm_filename,
                      const std::string &pal_filename,
                      const std::string output_filename)
{
  try
    {
      this->bm_file = load_file (bm_filename);
      this->pal_file = load_file (pal_filename);
    }
  catch (const std::exception &e)
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
  catch (const std::exception &e)
    {
      throw e;
    }

  this->output.emplace (output_filename, width, height);
  try
    {
      output->process_data (this->bm_file, this->pal_file);
      output->export_image ();
    }
  catch (const std::exception &e)
    {
      throw e;
    }
}

#include <format>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

static std::ifstream load_file (const std::string &filename);

int
main (void)
{
  const std::string bm_filename = "AUTOGRPH.BM";
  const std::string pal_filename = "AUTOGRPH.PAL";

  std::ifstream bm_file;
  std::ifstream pal_file;

  try
    {
      bm_file = load_file (bm_filename);
      pal_file = load_file (pal_filename);
    }
  catch (std::runtime_error &e)
    {
      std::cerr << e.what ();
      return -1;
    }

  return 0;
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

#include <format>
#include <fstream>
#include <iostream>
#include <string>

static std::ifstream load_file (const std::string &filename);

int
main (void)
{
  const std::string bm_filename = "AUTOGRPH.BM";
  const std::string pal_filename = "AUTOGRPH.PAL";

  std::ifstream bm_file = load_file (bm_filename);
  std::ifstream pal_file = load_file (pal_filename);

  bm_file.close ();
  pal_file.close ();

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

#include "converter.hpp"

#include <string>

int
main (void)
{
  const std::string bm_filename = "AUTOGRPH.BM";
  const std::string pal_filename = "AUTOGRPH.PAL";

  Converter c (bm_filename, pal_filename);

  return 0;
}

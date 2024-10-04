#include "converter.hpp"

#include <exception>
#include <format>
#include <iostream>
#include <stdexcept>

static void handle_improper_usage_error (const std::string &exe_name);
static void validate_user_input (const std::string &bm_filename,
                                 const std::string &pal_filename);

int
main (int argc, char **argv)
{
  if (argc < 3)
    handle_improper_usage_error (argv[0]);

  try
    {
      validate_user_input (argv[1], argv[2]);
    }
  catch (const std::runtime_error &e)
    {
      std::cerr << e.what ();
      handle_improper_usage_error (argv[0]);
    }

  const std::string bm_filename (argv[1]);
  const std::string pal_filename (argv[2]);

  std::cout << std::format ("Converting image, {}.\n", bm_filename);

  std::optional<Converter> c;
  try
    {
      c.emplace (bm_filename, pal_filename);
    }
  catch (const std::exception &e)
    {
      std::cerr << e.what ();
      exit (1);
    }

  std::cout << "Done!\n";

  return 0;
}

void
handle_improper_usage_error (const std::string &exe_name)
{
  std::cerr << std::format (
      "Improper usage.\n\ttry {} path/to/file.BM path/to/file.PAL\n",
      exe_name);
  exit (1);
}

void
validate_user_input (const std::string &bm_filename,
                     const std::string &pal_filename)
{
  if (bm_filename.length () < 3
      || (bm_filename.compare (bm_filename.length () - 3, 3, ".BM") != 0
          && bm_filename.compare (bm_filename.length () - 3, 3, ".bm") != 0))
    {
      throw std::runtime_error (
          std::format ("Error: {} is not a BM file.\n", bm_filename));
    }

  if (pal_filename.length () < 4
      || (pal_filename.compare (pal_filename.length () - 4, 4, ".PAL") != 0
          && pal_filename.compare (pal_filename.length () - 4, 4, ".pal")
                 != 0))
    {
      throw std::runtime_error (
          std::format ("Error: {} is not a PAL file.\n", pal_filename));
    }
}

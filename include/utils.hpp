#ifndef _UTILS_HPP_
#define _UTILS_HPP_

#include <cstdint>
#include <fstream>
#include <string>

std::ifstream load_file (const std::string &filename);
uint32_t read_uint32_from_file (std::ifstream &fptr);
void write_string_to_file (std::ofstream &fptr, const std::string &s);
void write_le_int_to_file (std::ofstream &fptr, const uint32_t x);
void write_le_int_to_file (std::ofstream &fptr, const uint16_t x);

#endif /* _UTILS_HPP_ */

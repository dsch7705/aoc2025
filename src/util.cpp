#include "util.h"

#include <filesystem>

std::ifstream get_input_stream(const char* path_to_src_file, const char* filename)
{
  auto inputPath = std::filesystem::path(path_to_src_file).parent_path() / filename;
  std::ifstream input(inputPath);
  if (!input.is_open()) {
    throw std::runtime_error(std::string("Failed to open input file ").append(inputPath.string()));
  }

  return input;
}

uint32_t pack_coord(uint16_t x, uint16_t y)
{
  return (static_cast<uint32_t>(x) << 16) | y;
}
void unpack_coord(uint32_t packed, uint16_t& x, uint16_t& y)
{
  x = (packed & 0xFFFF0000) >> 16;
  y = (packed & 0x0000FFFF);
}
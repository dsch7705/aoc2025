#include "util.h"

#include <filesystem>
#include <iostream>

std::ifstream get_input_stream(const char* path_to_src_file, const char* filename)
{
  auto inputPath = std::filesystem::path(path_to_src_file).parent_path() / filename;
  std::ifstream input(inputPath);
  if (!input.is_open()) {
    throw std::runtime_error(std::string("Failed to open input file ").append(inputPath.string()));
  }

  return input;
}
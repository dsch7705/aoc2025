#pragma once

#include <cstdint>
#include <fstream>

std::ifstream get_input_stream(const char* path_to_src_file, const char* filename);

uint32_t pack_coord(uint16_t x, uint16_t y);
void unpack_coord(uint32_t packed, uint16_t& x, uint16_t& y);
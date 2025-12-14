#include <cstdint>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include "../util.h"

std::unordered_map<uint32_t, size_t> split_map;
size_t beam(std::vector<std::string>& rows, uint16_t x, uint16_t y)
{
  size_t paths = 1;

  for (int i_y = y; i_y < rows.size(); i_y += 2) {
    uint32_t coord = pack_coord(x, i_y);
    char& ch = rows.at(i_y).at(x);
    if (ch == '^') {
      if (split_map.contains(coord)) {
        paths = split_map.at(coord);
        break;
      }

      paths = beam(rows, x + 1, i_y) + beam(rows, x - 1, i_y);
      split_map.insert(std::make_pair(coord, paths));
      break;
    }
  }

  return paths;
}

int main()
{
  std::ifstream input = get_input_stream(__FILE__, "input.txt");

  std::vector<std::string> rows;
  std::string line;
  while (std::getline(input, line)) {
    rows.push_back(line);
  }

  size_t pw = beam(rows, rows.at(0).find('S'), 0);

  std::cout << "Password: " << pw << std::endl;
  return 0;
}
#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "../util.h"

int main()
{
  int pw = 0;

  std::ifstream input = get_input_stream(__FILE__, "input.txt");

  std::vector<std::string> rows;
  std::string line;
  while (std::getline(input, line)) {
    rows.push_back(line);
  }

  std::stack<uint32_t> stack;
  stack.push(pack_coord(static_cast<uint16_t>(rows.at(0).find('S')), 0));

  while (!stack.empty()) {
    uint32_t coord = stack.top();
    stack.pop();

    uint16_t x, y;
    unpack_coord(coord, x, y);

    for (uint16_t i_y = y; i_y < rows.size(); i_y += 2) {
      if (rows.at(i_y).at(x) == '^') {
        uint32_t right = pack_coord(x + 1, i_y);
        uint32_t left = pack_coord(x - 1, i_y);

        char& right_ch = rows.at(i_y).at(x + 1);
        char& left_ch = rows.at(i_y).at(x - 1);

        int stack_size = stack.size();
        if (right_ch != '|') {
          stack.push(right);
          right_ch = '|';
        }
        if (left_ch != '|') {
          stack.push(left);
          left_ch = '|';
        }
        if (stack_size != stack.size())
          pw++;

        break;
      }
      else {
        rows.at(i_y).at(x) = '|';
      }
    }
  }

  std::cout << "Password: " << pw << std::endl;
  return 0;
}
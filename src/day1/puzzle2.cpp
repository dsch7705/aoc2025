#include <fstream>
#include <iostream>

#include "../util.h"

void rotate(int& pos, int& pw, int dir, int num)
{
  for (int i = 0; i < num; i++) {
    pos += dir;

    if (pos > 99) {
      pos = 0;
    }
    else if (pos < 0) {
      pos = 99;
    }

    if (pos == 0)
      pw++;
  }
}

int main(int argc, char** argv)
{
  std::ifstream input = get_input_stream(__FILE__, "input.txt");

  std::string line;
  int pos = 50;
  int pw = 0;

  while (std::getline(input, line)) {
    if (line.empty()) {
      break;
    }

    int dir = (line.at(0) == 'L') ? -1 : 1;
    int num = std::stoi(line.substr(1));

    rotate(pos, pw, dir, num);
  }

  std::cout << "Password: " << pw << std::endl;

  return 0;
}
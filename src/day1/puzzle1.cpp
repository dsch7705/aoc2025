#include <fstream>
#include <iostream>

#include "../util.h"

void rotate(int& pos, int dir, int num)
{
  pos += dir * num;
  if (pos > 99) {
    pos -= 100;
  }
  else if (pos < 0) {
    pos += 100;
  }

  if (pos > 99 || pos < 0)
    rotate(pos, 0, 0);
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

    rotate(pos, dir, num);
    if (pos == 0)
      pw++;
  }

  std::cout << "Password: " << pw << std::endl;

  return 0;
}
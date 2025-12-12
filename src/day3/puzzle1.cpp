#include <deque>
#include <iostream>
#include <string>
#include <vector>

#include "../util.h"

std::vector<std::string> get_banks()
{
  std::ifstream input = get_input_stream(__FILE__, "input.txt");
  std::vector<std::string> banks;
  std::string line;

  while (std::getline(input, line)) {
    banks.push_back(line);
  }
  return banks;
}

int main()
{
  int stack_size = 2;
  int pw = 0;

  auto banks = get_banks();
  for (const auto& bank : banks) {
    std::deque<char> deque;
    deque.push_back('0');
    for (int i = 0; i < bank.size(); i++) {
      char value = bank.at(i);
      while (!deque.empty() && value > deque.back()) {
        if ((bank.size() - i) <= stack_size - deque.size())
          break;
        deque.pop_back();
      }

      if (deque.size() < stack_size)
        deque.push_back(value);
    }

    std::string jolts;
    for (char c : deque) {
      jolts.push_back(c);
    }
    pw += std::stoi(jolts);
  }

  std::cout << "Password: " << pw << std::endl;
  return 0;
}
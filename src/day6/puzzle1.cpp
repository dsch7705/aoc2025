#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "../util.h"

void get_rows(std::vector<std::vector<int>>& nums, std::vector<char>& ops)
{
  std::ifstream input = get_input_stream(__FILE__, "input.txt");

  std::string line;
  while (std::getline(input, line)) {
    std::vector<int> num_row;

    std::stringstream ss(line);
    std::string line_str;
    char c;
    while (ss.get(c)) {
      if (c == ' ') {
        if (!line_str.empty()) {
          num_row.push_back(std::stoi(line_str));
        }
        line_str.clear();
      }
      else if (c >= '0' && c <= '9') {
        line_str.push_back(c);
      }
      else if (c == '+' || c == '*') {
        ops.push_back(c);
      }
    }
    if (!line_str.empty()) {
      num_row.push_back(std::stoi(line_str));
    }

    if (!num_row.empty())
      nums.push_back(std::move(num_row));
  }

  int n_problems = ops.size();
  std::cout << ops.size() << std::endl;
  for (const auto& row : nums) {
    if (row.size() != n_problems) {
      throw std::runtime_error("Mismatched rows");
    }
  }
}

int main()
{
  std::ifstream input = get_input_stream(__FILE__, "input.txt");

  std::vector<std::vector<int>> rows;
  std::vector<char> ops;
  get_rows(rows, ops);

  size_t pw = 0;

  for (int i = 0; i < ops.size(); i++) {
    std::vector<int> nums;
    for (const auto& row : rows) {
      nums.push_back(row.at(i));
    }

    size_t total = nums.at(0);
    for (int j = 1; j < nums.size(); j++) {
      if (ops.at(i) == '+') {
        total += nums.at(j);
      }
      else if (ops.at(i) == '*') {
        total *= nums.at(j);
      }
    }

    pw += total;
  }

  std::cout << "Password: " << pw << std::endl;
  return 0;
}
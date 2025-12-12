#include <iostream>
#include <string>
#include <vector>

#include "../util.h"

std::vector<std::string> get_rows()
{
  std::ifstream input = get_input_stream(__FILE__, "input.txt");
  std::vector<std::string> rows;

  std::string line;
  while (std::getline(input, line)) {
    rows.push_back(line);
  }

  int row_len = rows.at(0).size();
  for (const auto& row : rows) {
    if (row.size() != row_len) {
      throw std::runtime_error("Mismatched rows");
    }
  }
  return rows;
}

int main()
{
  size_t pw = 0;

  auto rows = get_rows();
  int row_len = rows.at(0).size();
  std::vector<int> nums;
  char op = 0;

  auto apply_op = [&] {
    size_t total = nums.at(0);
    std::cout << total << ' ';
    for (int k = 1; k < nums.size(); k++) {
      std::cout << op << ' ' << nums.at(k) << ' ';
      if (op == '+') {
        total += nums.at(k);
      }
      else if (op == '*') {
        total *= nums.at(k);
      }
    }
    std::cout << "= " << total << std::endl;
    pw += total;

    op = 0;
    nums.clear();
  };

  for (int i = 0; i < row_len; i++) {
    std::string num_str;
    for (int j = 0; j < rows.size(); j++) {
      const auto& row = rows.at(j);
      char digit = row.at(i);

      if (digit >= '0' && digit <= '9') {
        num_str.push_back(digit);
      }
      else if (digit == '+' || digit == '*') {
        op = digit;
      }
    }
    if (!num_str.empty()) {
      nums.push_back(std::stoi(num_str));
      num_str.clear();
    }
    else {
      apply_op();
    }
  }

  if (!nums.empty())
    apply_op();

  std::cout << "Password: " << pw << std::endl;
  return 0;
}
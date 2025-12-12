#include <cmath>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

#include "../util.h"

std::vector<std::pair<size_t, size_t>> get_ranges()
{
  std::ifstream input = get_input_stream(__FILE__, "input.txt");

  std::vector<std::pair<size_t, size_t>> ranges;

  std::string range_str;
  while (std::getline(input, range_str, ',')) {
    int dash_idx = range_str.find('-');

    std::string start_str = range_str.substr(0, dash_idx);
    size_t start = std::stoul(start_str);

    std::string end_str = range_str.substr(dash_idx + 1);
    size_t end = std::stoul(end_str);

    ranges.push_back(std::make_pair(start, end));
  }

  return ranges;
}

size_t get_digits(size_t num, size_t offset, size_t count = 0)
{
  int n_digits = std::floor(std::log10(num)) + 1;

  size_t n = num % static_cast<size_t>(std::pow(10, n_digits - offset));
  if (count > 0) {
    n = std::floor(n / std::pow(10, (n_digits - offset) - count));
  }

  return n;
}

int main(int argc, char** argv)
{
  size_t pw = 0;

  for (const auto range : get_ranges()) {
    for (size_t i = range.first; i <= range.second; i++) {
      int n_digits = std::floor(std::log10(i)) + 1;

      bool match = false;
      for (int j = 1; j < n_digits; j++) {
        if (n_digits % j != 0)
          continue;
        size_t pattern = get_digits(i, 0, j);

        bool is_match = true;
        for (int k = 0; k < n_digits / j; k++) {
          size_t sub = get_digits(i, k * j, j);
          if (sub != pattern) {
            is_match = false;
          }
        }

        if (is_match) {
          match = true;
          break;
        }
      }

      if (match)
        pw += i;
    }
  }

  std::cout << "Password: " << pw << std::endl;
  return 0;
}
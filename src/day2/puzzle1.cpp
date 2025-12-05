#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

std::vector<std::pair<size_t, size_t>> get_ranges()
{
  auto inputPath = std::filesystem::path(__FILE__).parent_path() / "input1.txt";
  std::ifstream input(inputPath);

  if (!input.is_open()) {
    std::cerr << "Failed to open input file!" << std::endl;
    return {};
  }

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

int main(int argc, char** argv)
{
  size_t pw = 0;

  for (const auto range : get_ranges()) {
    for (size_t i = range.first; i <= range.second; i++) {
      int n_digits = std::floor(std::log10(i)) + 1;
      if (n_digits % 2 != 0)
        continue;

      size_t first_half = std::floor(i / std::pow(10, n_digits / 2));
      size_t second_half = i % static_cast<size_t>(std::floor(std::pow(10, n_digits / 2)));

      if (first_half == second_half)
        pw += i;
    }
  }

  std::cout << "Password: " << pw << std::endl;
  return 0;
}
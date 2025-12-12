#include <iostream>
#include <vector>

#include "../util.h"

typedef std::pair<size_t, size_t> range_t;
typedef std::vector<range_t> range_list_t;

constexpr range_t kZeroPair{0, 0};

void get_input(range_list_t& ranges)
{
  std::ifstream input = get_input_stream(__FILE__, "input.txt");
  std::string line;

  while (std::getline(input, line)) {
    if (line.empty()) {
      break;
    }

    int delim_idx = line.find('-');
    size_t begin = std::stoul(line.substr(0, delim_idx));
    size_t end = std::stoul(line.substr(delim_idx + 1));

    ranges.emplace_back(begin, end);
  }
}

void trim_range(const range_t& rng, range_list_t& known)
{
  auto trim = [](const range_t& range, const range_t& known_range) -> std::pair<range_t, range_t> {
    std::pair<range_t, range_t> new_ranges;

    if (range.first >= known_range.first && range.first <= known_range.second && range.second <= known_range.second) {
      return new_ranges;
    }
    else if (range.first >= known_range.first && range.first <= known_range.second) {
      new_ranges.first = std::make_pair(known_range.second + 1, range.second);
    }
    else if (range.second >= known_range.first && range.second <= known_range.second) {
      new_ranges.first = std::make_pair(range.first, known_range.first - 1);
    }
    else if (known_range.first >= range.first && known_range.first <= range.second &&
             known_range.second >= range.first && known_range.second <= range.second) {
      new_ranges.first = std::make_pair(range.first, known_range.first - 1);
      new_ranges.second = std::make_pair(known_range.second + 1, range.second);
    }
    else {
      new_ranges.first = range;
    }

    return new_ranges;
  };

  range_list_t trimmed{rng};
  for (const auto& known_range : known) {
    range_list_t tmp;
    for (const auto& range : trimmed) {
      auto range_pair = trim(range, known_range);
      if (range_pair.first == kZeroPair)
        continue;

      tmp.push_back(range_pair.first);
      if (range_pair.second != kZeroPair) {
        tmp.push_back(range_pair.second);
      }
    }
    trimmed = std::move(tmp);
  }

  for (const auto& range : trimmed) {
    known.push_back(range);
  }
}

int main()
{
  size_t pw = 0;

  range_list_t known;
  range_list_t ranges;
  get_input(ranges);

  for (const auto& range : ranges) {
    trim_range(range, known);
  }
  for (const auto& known_range : known) {
    pw += (known_range.second - known_range.first) + 1;
  }

  std::cout << "Password: " << pw << std::endl;
  return 0;
}
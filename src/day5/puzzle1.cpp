#include <iostream>
#include <unordered_set>
#include <vector>

#include "../util.h"

void get_input(std::vector<std::pair<size_t, size_t>>& ranges, std::vector<size_t>& ids)
{
  std::ifstream input = get_input_stream(__FILE__, "input.txt");
  std::string line;
  bool second_list = false;  // Are we on the ID list section?

  while (std::getline(input, line)) {
    if (line.empty()) {
      second_list = true;
      continue;
    }

    if (second_list) {
      ids.push_back(std::stoul(line));
    }
    else {
      int delim_idx = line.find('-');
      size_t begin = std::stoul(line.substr(0, delim_idx));
      size_t end = std::stoul(line.substr(delim_idx + 1));

      ranges.emplace_back(begin, end);
    };
  }
}

int main()
{
  std::vector<std::pair<size_t, size_t>> ranges;
  std::vector<size_t> ids;
  get_input(ranges, ids);

  std::unordered_set<size_t> fresh;
  for (auto& range : ranges) {
    for (auto id : ids) {
      if (fresh.find(id) != fresh.end())
        continue;

      if (id >= range.first && id <= range.second) {
        fresh.insert(id);
      }
    }
  }

  std::cout << "Password: " << fresh.size() << std::endl;
  return 0;
}
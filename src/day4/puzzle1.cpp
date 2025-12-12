#include <iostream>
#include <string>
#include <vector>

#include "../util.h"

class RollGrid {
 private:
  struct Cell {
    bool occupied{false};
    int neighbors{0};
  };

  std::vector<std::vector<Cell>> m_grid;
  std::vector<std::string> m_raw_input;
  int m_w, m_h;

  int m_accessible_cells{0};

  Cell* get_cell(int x, int y)
  {
    if (x < 0 || x >= m_w || y < 0 || y >= m_h)
      return nullptr;

    return &m_grid.at(y).at(x);
  }

  void populate()
  {
    for (int y = 0; y < m_h; y++) {
      std::string row = m_raw_input.at(y);
      for (int x = 0; x < m_w; x++) {
        char c = row.at(x);
        if (c != '@')
          continue;

        get_cell(x, y)->occupied = true;

        // Update neighbors
        auto update_neighbor = [this](int x, int y) {
          Cell* neighbor = get_cell(x, y);
          if (neighbor)
            neighbor->neighbors++;
        };

        update_neighbor(x + 1, y);
        update_neighbor(x + 1, y + 1);
        update_neighbor(x, y + 1);
        update_neighbor(x - 1, y + 1);
        update_neighbor(x - 1, y);
        update_neighbor(x - 1, y - 1);
        update_neighbor(x, y - 1);
        update_neighbor(x + 1, y - 1);
      }
    }

    for (const auto& row : m_grid) {
      for (const auto& cell : row) {
        if (cell.occupied && cell.neighbors < 4) {
          m_accessible_cells++;
        }
      }
    }
  }

 public:
  RollGrid(const char* input_filename)
  {
    std::ifstream input = get_input_stream(__FILE__, input_filename);
    std::string line;

    while (std::getline(input, line)) {
      m_raw_input.push_back(line);
    }

    m_grid.resize(m_raw_input.size());
    m_h = m_grid.size();
    m_w = m_raw_input.at(0).size();
    for (auto& row : m_grid) {
      row.resize(m_w);
    }

    populate();
  }

  int w() const { return m_w; }
  int h() const { return m_h; }

  int accessible_cells() const { return m_accessible_cells; }
};

int main()
{
  RollGrid rg("input.txt");
  std::cout << "Password: " << rg.accessible_cells() << std::endl;
}
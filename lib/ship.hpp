#pragma once

#include "common.hpp"

class Ship {
 public:
  Ship() = default;
  Ship(const std::vector<Cell*>& chosen_cells);
  ~Ship() {
    std::cout << "cringe " << GetSize() << "\n";
    std::cout.flush();
  };
  Ship(const Ship& ship) : health_(ship.health_), cells_(ship.cells_) {}
  Ship& operator=(Ship ship) {
    std::swap(health_, ship.health_);
    std::swap(cells_, ship.cells_);
    return *this;
  }
  
  void Clear();
  void DecrementHealth();
  bool IsAlive() const;
  const deque<Cell*>& GetCells() const;
  size_t GetSize() const;
  void AddCell(Cell* cell_);
  void EraseCell(Cell* cell_);
  bool IsClassic() const;

 protected:
  int health_;
  deque<Cell*> cells_;
};

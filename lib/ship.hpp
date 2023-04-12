#pragma once

#include "common.hpp"

class Ship {
 public:
  Ship() = default;
  Ship(const deque<Cell*>& chosen_cells);
  ~Ship() = default;

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

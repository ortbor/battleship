#pragma once

#include "common.hpp"

class Ship {
 public:
  Ship() = default;
  Ship(const std::vector<Cell*>& chosen_cells);
  ~Ship() = default;
  
  void Clear();
  void DecrementHealth();
  bool IsAlive() const;
  const vector<Cell*>& GetCells() const;
  size_t GetSize() const;
  void AddCell(Cell* cell_);
  void EraseCell(Cell* cell_);
  bool IsClassic() const;

 protected:
  size_t health_;
  vector<Cell*> cells_;
};

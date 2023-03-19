#pragma once

#include "common.hpp"
#include "cell.hpp"

class Ship {
 public:
  ~Ship() = default;
  Ship() = default;
  Ship(const std::vector<Cell*>& chosen_cells);
  void Clear();
  void DecrementHealth();
  bool IsAlive() const;
  const std::vector<Cell*>& GetCells() const;
  size_t GetSize() const;
  void AddCell(Cell* cell_);
  void EraseCell(Cell* cell_);
  bool IsClassic() const;

 protected:
  size_t health_;
  std::vector<Cell*> cells_;
};
#pragma once

#include "common.hpp"

class Cell {
 public:
  Cell();
  ~Cell() = default;

  State GetState() const;
  void SetState(State state);

  Ship* GetShip() const;
  void SetShip(Ship* ship);

  Cell* GetTwin() const;
  void LinkCell(Cell* other_cell);

  size_t GetW() const;
  size_t GetL() const;
  void SetCoords(size_t w_coord, size_t l_coord);

 protected:
  size_t w_coord_, l_coord_;
  State state_;
  Ship* ship_;
  Cell* twin_cell_;
};

bool comparator(Cell* cell1, Cell* cell2);
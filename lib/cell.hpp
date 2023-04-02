#pragma once

#include "common.hpp"

struct Cell {
  Cell();
  Cell(const Vector2f& coordn);
  ~Cell() = default;

  void LinkCell(Cell* other_cell);

  Vector2f coord;
  State state;
  Ship* ship;
  Cell* twin_cell;
};

bool CellComparator(const Cell* cell1, const Cell* cell2);

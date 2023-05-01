#pragma once

#include "cell.hpp"
#include "common.hpp"

class Field {
 public:
  Field(const Vector2u& size);
  ~Field() = default;
  void LinkField(Field* other);

  Cell* GetCell(const Vector2u& coord);
  void SurroundExcept(Cell* cell, CellState around, CellState except);

  virtual void Clear() = 0;

 protected:
  Vector2f m_size;
  deque<deque<Cell>> m_cells;
};

class MyField : public Field {
 public:
  MyField(const Vector2u& size);
  void SetShip(Ship* ship);
  void RemoveProhibited();

  void Clear() final;
};

class RivalField : public Field {
 public:
  RivalField(const Vector2u& size);
  void UpdateShot(Cell* cell, ShotState& shot_result);

  void Clear() final;
};

#pragma once

#include "common.hpp"

class Field {
 public:
  Field(const Vector2f& sizen);
  ~Field() = default;
  void LinkField(Field* other_field);

  Cell* GetCell(const Vector2f& coord);
  void SurroundExcept(Cell* cell, State around, State except);

  virtual void Clear() = 0;

 protected:
  Vector2f size_;
  deque<deque<Cell>> cells_;
};

class MyField : public Field {
 public:
  MyField(const Vector2f& sizen);
  void SetShip(Ship* ship);

  void Clear() final;
};

class RivalField : public Field {
 public:
  RivalField(const Vector2f& sizen);
  void UpdateShot(Cell* cell, ShotResult& shot_result);

  void Clear() final;
};

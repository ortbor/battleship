#pragma once

#include "cell.hpp"
#include "ship.hpp"

class Field {
 public:
  ~Field() = default;
  Field(int length, int width);
  void LinkField(Field* other_field);

 protected:
  size_t length_, width_;
  std::vector<std::vector<Cell>> cells_;
};

class MyField : public Field {
 public:
  MyField(int length, int width);
  void SetShip(Ship* ship);
};

class RivalField : public Field {
 public:
  RivalField(int length, int width);
  void UpdateShot(Cell* cell, ShotResult& shot_result);
};
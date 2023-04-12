#pragma once

#include "common.hpp"

class Cell {
  public:
  Cell(const Vector2f& coord);
  ~Cell() = default;

  const Vector2f& GetCoord() const;
  State GetState() const;
  Ship* GetShip() const;
  Cell* GetTwin() const;
  sf::RectangleShape* GetShape() const;
  void SetState(State state);
  void TryToProhibit();
  void SetShip(Ship* ship);
  void SetTwins(Cell* other_cell);
  void SetShape(sf::RectangleShape* shape);

 private:
  Vector2f coord_;
  State state_;
  Ship* ship_;
  Cell* twin_cell_;
  sf::RectangleShape* shape_;

  void UpdateColor();
};

bool CellComparator(const Cell* cell1, const Cell* cell2);

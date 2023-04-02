#include "../lib/cell.hpp"

Cell::Cell()
    : coord(0, 0), state(State::Unknown), ship(nullptr), twin_cell(nullptr) {}

Cell::Cell(const Vector2f& coordn)
    : coord(coordn), state(State::Unknown), ship(nullptr), twin_cell(nullptr) {}

void Cell::LinkCell(Cell* other_cell) {
  twin_cell = other_cell;
  other_cell->twin_cell = this;
}

bool CellComparator(const Cell* cell1, const Cell* cell2) {
  return cell1->coord.x < cell2->coord.x ||
         (cell1->coord.x == cell2->coord.x && cell1->coord.y < cell2->coord.y);
}

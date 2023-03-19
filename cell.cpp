#include "cell.hpp"

Cell::Cell() { state_ = State::Unknown; }

void Cell::SetShip(Ship* ship) { ship_ = ship; }

void Cell::SetState(State state) { state_ = state; }

State Cell::GetState() const { return state_; }

Cell* Cell::GetTwin() const { return twin_cell_; }

Ship* Cell::GetShip() const { return ship_; }

void Cell::LinkCell(Cell* other_cell) {
  twin_cell_ = other_cell;
  other_cell->twin_cell_ = this;
}

void Cell::SetCoords(size_t w_coord, size_t l_coord) {
  w_coord_ = w_coord;
  l_coord_ = l_coord;
}

size_t Cell::GetW() const { return w_coord_; }

size_t Cell::GetL() const { return l_coord_; }

bool comparator(Cell* cell1, Cell* cell2) {
  return cell1->GetW() < cell2->GetW() ||
         (cell1->GetW() == cell2->GetW() && cell1->GetL() < cell2->GetL());
}
#include "../lib/ship.hpp"

#include "../lib/cell.hpp"

Ship::Ship(const std::vector<Cell*>& chosen_cells)
    : health_(chosen_cells.size()), cells_(chosen_cells) {
  std::sort(cells_.begin(), cells_.end(), CellComparator);
}

void Ship::Clear() {
  health_ = 0;
  cells_.clear();
}

void Ship::DecrementHealth() {
  if (health_ > 0) {
    --health_;
  }
}

bool Ship::IsAlive() const { return health_ > 0; }

const vector<Cell*>& Ship::GetCells() const { return cells_; }

size_t Ship::GetSize() const { return cells_.size(); }

void Ship::AddCell(Cell* cell) {
  ++health_;
  cells_.push_back(cell);
  cell->state = State::Chosen;
  size_t new_cell_index = GetSize() - 1;
  while (new_cell_index > 0 &&
         !CellComparator(cells_[new_cell_index - 1], cells_[new_cell_index])) {
    std::swap(cells_[new_cell_index], cells_[new_cell_index - 1]);
    --new_cell_index;
  }
}

void Ship::EraseCell(Cell* cell) {
  auto cell_location = find(cells_.begin(), cells_.end(), cell);
  if (cell_location != cells_.end()) {
    if (cell->state != State::Killed && cell->state != State::Harmed) {
      --health_;
    }
    cells_.erase(find(cells_.begin(), cells_.end(), cell));
    cell->state = State::Clear;
  }
}

bool Ship::IsClassic() const {
  if (GetSize() == 1) {
    return true;
  }
  if (GetSize() > 4 || GetSize() == 0) {
    return false;
  }
  bool vertical = false;
  if (cells_[0]->coord.y == cells_[1]->coord.y) {
    vertical = true;
  }
  for (size_t i = 0; i < GetSize() - 1; ++i) {
    if ((vertical && cells_[i + 1]->coord.y == cells_[i + 1]->coord.y &&
         cells_[i]->coord.x + 1 == cells_[i + 1]->coord.x) ||
        (!vertical && cells_[i]->coord.x == cells_[i + 1]->coord.x &&
         cells_[i]->coord.y + 1 == cells_[i + 1]->coord.y)) {
      continue;
    }
    return false;
  }
  return true;
}

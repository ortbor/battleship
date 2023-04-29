#include "ship.hpp"

Ship::Ship(const std::vector<Cell*>& chosen_cells)
    : health_(chosen_cells.size()),
      cells_(chosen_cells) {
  std::sort(cells_.begin(), cells_.end(), comparator);
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

const std::vector<Cell*>& Ship::GetCells() const { return cells_; }

size_t Ship::GetSize() const { return cells_.size(); }

void Ship::AddCell(Cell* cell) {
  ++health_;
  cells_.push_back(cell);
  size_t new_cell_index = GetSize() - 1;
  while (new_cell_index > 0 && !comparator(cells_[new_cell_index - 1],
                                           cells_[new_cell_index])) {
    std::swap(cells_[new_cell_index], cells_[new_cell_index - 1]);
    --new_cell_index;
  }
}

void Ship::EraseCell(Cell* cell) {
  auto cell_location = find(cells_.begin(), cells_.end(), cell);
  if (cell_location != cells_.end()) {
    if (!(cell->GetState() == State::Killed || cell->GetState() == State::Harmed)) {
      --health_;
    }
    cells_.erase(find(cells_.begin(), cells_.end(), cell));
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
  if (cells_[0]->GetL() == cells_[1]->GetL()) {
    vertical = true;
  }
  for (int i = 0; i < GetSize() - 1; ++i) {
    if ((vertical && cells_[i + 1]->GetL() == cells_[i + 1]->GetL()
                  && cells_[i]->GetW() + 1 == cells_[i + 1]->GetW()) ||
        (!vertical && cells_[i]->GetW() == cells_[i + 1]->GetW()
                   && cells_[i]->GetL() + 1 == cells_[i + 1]->GetL())) {
      continue;
    }
    return false;
  }
  return true;
}
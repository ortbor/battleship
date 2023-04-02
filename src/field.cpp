#include "../lib/field.hpp"

#include "../lib/cell.hpp"
#include "../lib/ship.hpp"

Field::Field(const Vector2f& sizen)
    : size_(sizen),
      cells_(vector<vector<Cell>>(size_.x, vector<Cell>(size_.y))) {
  for (size_t i = 0; i < size_.x; ++i) {
    for (size_t j = 0; j < size_.y; ++j) {
      cells_[i][j].coord.x = i;
      cells_[i][j].coord.y = j;
    }
  }
}

void Field::LinkField(Field* other_field) {
  for (size_t i = 0; i < size_.x; ++i) {
    for (size_t j = 0; j < size_.y; ++j) {
      cells_[i][j].LinkCell(&other_field->cells_[i][j]);
    }
  }
}

Cell* Field::GetCell(const Vector2f& coord) {
  return cells_[coord.x].data() + Vector2u(coord).y;
}

MyField::MyField(const Vector2f& sizen) : Field(sizen) {
  for (size_t i = 0; i < sizen.x; ++i) {
    for (size_t j = 0; j < sizen.y; ++j) {
      cells_[i][j].state = State::Clear;
    }
  }
}

void MyField::SetShip(Ship* ship) {
  for (Cell* cell : ship->GetCells()) {
    cell->state = State::Alive;
    cell->ship = ship;
    size_t current_w = cell->coord.x;
    size_t current_l = cell->coord.y;
    if (current_w != 0) {
      cells_[current_w - 1][current_l].state = State::Prohibited;
      if (current_l != 0) {
        cells_[current_w - 1][current_l - 1].state = State::Prohibited;
      }
      if (current_l != size_.y - 1) {
        cells_[current_w - 1][current_l + 1].state = State::Prohibited;
      }
    }
    if (current_w != size_.x - 1) {
      cells_[current_w + 1][current_l].state = State::Prohibited;
      if (current_l != 0) {
        cells_[current_w + 1][current_l - 1].state = State::Prohibited;
      }
      if (current_l != size_.y - 1) {
        cells_[current_w + 1][current_l + 1].state = State::Prohibited;
      }
    }
    if (current_l != 0) {
      cells_[current_w][current_l - 1].state = State::Prohibited;
    }
    if (current_l != size_.y - 1) {
      cells_[current_w][current_l + 1].state = State::Prohibited;
    }
  }
}

RivalField::RivalField(const Vector2f& sizen) : Field(sizen) {}

void RivalField::UpdateShot(Cell* cell, ShotResult& shot_result) {
  Cell* twin = cell->twin_cell;
  if (twin->state == State::Alive) {
    cell->state = State::Harmed;
    twin->state = State::Harmed;
    twin->ship->DecrementHealth();
    if (!twin->ship->IsAlive()) {
      std::cout << "Kill.\n";
      shot_result = ShotResult::Kill;
      for (Cell* killed_cell : twin->ship->GetCells()) {
        killed_cell->state = State::Killed;
        killed_cell->twin_cell->state = State::Killed;
      }
    } else {
      std::cout << "Harm.\n";
      shot_result = ShotResult::Harm;
    }
  } else if (twin->state == State::Clear) {
    cell->state = State::Missed;
    twin->state = State::Missed;
    std::cout << "Miss.\n";
    shot_result = ShotResult::Miss;
  } else {
    std::cout << "Miss.\n";
    shot_result = ShotResult::Miss;
  }
}

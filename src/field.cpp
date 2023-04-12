#include "../lib/field.hpp"

#include "../lib/cell.hpp"
#include "../lib/ship.hpp"

Field::Field(const Vector2f& sizen)
    : size_(sizen), cells_(vector<vector<Cell>>(size_.x)) {
  for (size_t i = 0; i < size_.x; ++i) {
    for (size_t j = 0; j < size_.y; ++j) {
      cells_[i].push_back(Cell(Vector2f(i, j)));
    }
  }
}

void Field::LinkField(Field* other_field) {
  for (size_t i = 0; i < size_.x; ++i) {
    for (size_t j = 0; j < size_.y; ++j) {
      cells_[i][j].SetTwins(&other_field->cells_[i][j]);
    }
  }
}

Cell* Field::GetCell(const Vector2f& coord) {
  return cells_[coord.x].data() + Vector2u(coord).y;
}

MyField::MyField(const Vector2f& sizen) : Field(sizen) {
  for (size_t i = 0; i < sizen.x; ++i) {
    for (size_t j = 0; j < sizen.y; ++j) {
      cells_[i][j].SetState(State::Clear);
    }
  }
}

void MyField::SetShip(Ship* ship) {
  for (Cell* cell : ship->GetCells()) {
    cell->SetState(State::Alive);
    cell->SetShip(ship);
    size_t current_w = cell->GetCoord().x;
    size_t current_l = cell->GetCoord().y;
    if (current_w != 0) {
      cells_[current_w - 1][current_l].TryToProhibit();
      if (current_l != 0) {
        cells_[current_w - 1][current_l - 1].TryToProhibit();
      }
      if (current_l != size_.y - 1) {
        cells_[current_w - 1][current_l + 1].TryToProhibit();
      }
    }
    if (current_w != size_.x - 1) {
      cells_[current_w + 1][current_l].TryToProhibit();
      if (current_l != 0) {
        cells_[current_w + 1][current_l - 1].TryToProhibit();
      }
      if (current_l != size_.y - 1) {
        cells_[current_w + 1][current_l + 1].TryToProhibit();
      }
    }
    if (current_l != 0) {
      cells_[current_w][current_l - 1].TryToProhibit();
    }
    if (current_l != size_.y - 1) {
      cells_[current_w][current_l + 1].TryToProhibit();
    }
  }
}

RivalField::RivalField(const Vector2f& sizen) : Field(sizen) {}

void RivalField::UpdateShot(Cell* cell, ShotResult& shot_result) {
  Cell* twin = cell->GetTwin();
  if (twin->GetState() == State::Alive) {
    cell->SetState(State::Harmed);
    twin->SetState(State::Harmed);
    twin->GetShip()->DecrementHealth();
    std::cout << twin->GetShip()->health_ << "\n";
    if (!twin->GetShip()->IsAlive()) {
      std::cout << "Kill.\n";
      shot_result = ShotResult::Kill;
      for (Cell* killed_cell : twin->GetShip()->GetCells()) {
        killed_cell->SetState(State::Killed);
        killed_cell->GetTwin()->SetState(State::Killed);
      }
    } else {
      std::cout << "Harm.\n";
      shot_result = ShotResult::Harm;
    }
  } else if (twin->GetState() == State::Clear) {
    cell->SetState(State::Missed);
    twin->SetState(State::Missed);
    std::cout << "Miss.\n";
    shot_result = ShotResult::Miss;
  } else {
    std::cout << "Miss.\n";
    shot_result = ShotResult::Miss;
  }
}

#include "field.hpp"

Field::Field(int length, int width)
    : length_(length), width_(width),
      cells_(std::vector<std::vector<Cell>>(width, std::vector<Cell>(length))) {
  for (size_t i = 0; i < width; ++i) {
    for (size_t j = 0; j < length; ++j) {
      cells_[i][j].SetCoords(i, j);
    }
  }
}

void Field::LinkField(Field* other_field) {
  for (size_t i = 0; i < width_; ++i) {
    for (size_t j = 0; j < length_; ++j) {
      cells_[i][j].LinkCell(&other_field->cells_[i][j]);
    }
  }
}

MyField::MyField(int length, int width) : Field(length_, width_)  {
  for (size_t i = 0; i < width; ++i) {
    for (size_t j = 0; j < length; ++j) {
      cells_[i][j].SetState(State::Clear);
    }
  }
}

void MyField::SetShip(Ship* ship) {
  for (Cell* cell : ship->GetCells()) {
    cell->SetState(State::Alive);
    cell->SetShip(ship);
    size_t current_w = cell->GetW(), current_l = cell->GetL();
    if (current_w != 0) {
      cells_[current_w - 1][current_l].SetState(State::Prohibited);
      if (current_l != 0) {
        cells_[current_w - 1][current_l - 1].SetState(State::Prohibited);
      }
      if (current_l != length_ - 1) {
        cells_[current_w - 1][current_l + 1].SetState(State::Prohibited);
      }
    }
    if (current_w != width_ - 1) {
      cells_[current_w + 1][current_l].SetState(State::Prohibited);
      if (current_l != 0) {
        cells_[current_w + 1][current_l - 1].SetState(State::Prohibited);
      }
      if (current_l != length_ - 1) {
        cells_[current_w + 1][current_l + 1].SetState(State::Prohibited);
      }
    }
    if (current_l != 0) {
      cells_[current_w][current_l - 1].SetState(State::Prohibited);
    }
    if (current_l != length_ - 1) {
      cells_[current_w][current_l + 1].SetState(State::Prohibited);
    }
  }
}

RivalField::RivalField(int length, int width) : Field(length, width) {}

void RivalField::UpdateShot(Cell* cell, ShotResult& shot_result) {
  Cell* twin = cell->GetTwin();
  if (twin->GetState() == State::Alive) {
    cell->SetState(State::Harmed);
    twin->SetState(State::Harmed);
    twin->GetShip()->DecrementHealth();
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
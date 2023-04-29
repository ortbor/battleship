#include "command.hpp"

Command::Command(Player* player) : player_(player) {}

AddCellToShipCommand::AddCellToShipCommand(Player* player, Cell* cell)
    : Command(player), cell_(cell) {}

void AddCellToShipCommand::Execute() {
  player_->ship_in_process_.AddCell(cell_);
  //cell_->Color(State::Chosen);
}

void AddCellToShipCommand::Undo() {
  player_->ship_in_process_.EraseCell(cell_);
  //cell_->Color(State::Clear);
}

bool AddCellToShipCommand::IsValid() const {
  return cell_->GetState() == State::Clear;
}

AddShipCommand::AddShipCommand(Player* player) : Command(player) {}

void AddShipCommand::Execute() {
  for (Cell* added_cell : player_->GetShipInProcess()->GetCells()) {
   // added_cell->Color(State::Alive);
  }
  player_->AddShip();
  player_->FinishSettingShip();
}

bool AddShipCommand::IsValid() const {
  if (!player_->GetShipInProcess()->IsClassic()) {
    return false;
  }
  if (player_->GetNumberOfShipsSized(player_->GetShipInProcess()->GetSize()) >=
      5 - player_->GetShipInProcess()->GetSize()) {
    return false;
  }
  for (Cell *cell: player_->GetShipInProcess()->GetCells()) {
    if (cell->GetState() != State::Clear) {
      return false;
    }
  }
  return true;
}

ShootCommand::ShootCommand(Player* player, Cell* cell) : Command(player), cell_(cell) {}

void ShootCommand::Execute() {
  ShotResult shot_result;
  player_->Shoot(cell_, shot_result);
  if (shot_result == ShotResult::Miss) {
   // cell_->Color(State::Clear);
  } else if (shot_result == ShotResult::Harm) {
   // cell_->Color(State::Harmed);
  } else if (shot_result == ShotResult::Kill) {
    for (Cell* killed_cell : cell_->GetTwin()->GetShip()->GetCells()) {
    //  killed_cell->Color(State::Killed);
    }
  }
}

bool ShootCommand::IsValid() const { return true; }
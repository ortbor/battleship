#include "../lib/command.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/player.hpp"
#include "../lib/window.hpp"

Command::Command(Player* player, GameWindow* windown)
    : player_(player), window_(windown) {}

CloseCommand::CloseCommand(GameWindow* windown) : Command(nullptr, windown) {}

bool CloseCommand::Execute() {
  window_->close();
  return true;
}

bool CloseCommand::IsValid() const { return true; }

ResizeCommand::ResizeCommand(GameWindow* windown) : Command(nullptr, windown) {}

bool ResizeCommand::Execute() {
  window_->UpdateSize();
  window_->DrawObjects();
  return true;
}

bool ResizeCommand::IsValid() const { return true; }

AddCellToShipCommand::AddCellToShipCommand(Player* player, GameWindow* windown,
                                           Cell* cell)
    : Command(player, windown), cell_(cell) {}

bool AddCellToShipCommand::Execute() {
  bool valid = IsValid();
  if (valid) {
    if (cell_->GetState() == State::Clear) {
      player_->ship_in_process_.AddCell(cell_);
    } else {
      player_->ship_in_process_.EraseCell(cell_);
    }
    window_->DrawObjects();
  }
  return valid;
}

bool AddCellToShipCommand::IsValid() const {
  return cell_->GetState() == State::Clear ||
         cell_->GetState() == State::Chosen;
}

AddShipCommand::AddShipCommand(Player* player, GameWindow* windown)
    : Command(player, windown) {}

bool AddShipCommand::Execute() {
  bool valid = IsValid();
  if (valid) {
    player_->AddShip();
    window_->DrawObjects();
  }
  return valid;
}

bool AddShipCommand::IsValid() const {
  if (!player_->GetShipInProcess()->IsClassic()) {
    return false;
  }
  if (player_->GetNumberOfShipsSized(player_->GetShipInProcess()->GetSize()) >=
      5 - player_->GetShipInProcess()->GetSize()) {
    return false;
  }

  auto cells = player_->GetShipInProcess()->GetCells();
  return std::all_of(cells.begin(), cells.end(), [](const Cell* cell) {
    return cell->GetState() != State::Clear;
  });
}

ShootCommand::ShootCommand(Player* player, GameWindow* windown, Cell* cell)
    : Command(player, windown), cell_(cell) {}

bool ShootCommand::Execute() {
  bool valid = IsValid();
  if (valid) {
    ShotResult shot_result;
    player_->Shoot(cell_, shot_result);
    if (shot_result == ShotResult::Miss) {
      // cell_->Color(State::Clear);
    } else if (shot_result == ShotResult::Harm) {
      // cell_->Color(State::Harmed);
    } else if (shot_result == ShotResult::Kill) {
      // for (auto killed_cell : cell_->GetTwin()->GetShip()->GetCells()) {
      //  killed_cell->Color(State::Killed);
      //}
    }
  }
  return valid;
}

bool ShootCommand::IsValid() const { return true; }

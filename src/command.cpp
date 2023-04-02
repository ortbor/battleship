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
    if (cell_->state == State::Clear) {
      player_->ship_in_process_.AddCell(cell_);
    } else {
      player_->ship_in_process_.EraseCell(cell_);
    }
    for (const auto& item : window_->GetButtons()) {
      if (item->GetCommand() == this) {
        auto* obj = dynamic_cast<sf::RectangleShape*>(item->GetDrawable()[0]);
        auto color = obj->getFillColor();
        obj->setFillColor(sf::Color(255 - color.r, 255 - color.g, 255 - color.b));
        window_->DrawObjects();
        break;
      }
    }
  }
  return valid;
}

void AddCellToShipCommand::Undo() {
  player_->ship_in_process_.EraseCell(cell_);
  for (const auto& item : window_->GetButtons()) {
    if (item->GetCommand() == this) {
      auto* obj = dynamic_cast<sf::RectangleShape*>(item->GetDrawable()[0]);
      auto color = obj->getFillColor();
      obj->setFillColor(sf::Color(color.r, color.g, 255 - color.b));
      window_->DrawObjects();
      break;
    }
  }
}

bool AddCellToShipCommand::IsValid() const {
  return cell_->state == State::Clear || cell_->state == State::Chosen;
}

AddShipCommand::AddShipCommand(Player* player, GameWindow* windown)
    : Command(player, windown) {}

bool AddShipCommand::Execute() {
  bool valid = IsValid();
  if (valid) {
    // for (auto added_cell : player_->GetShipInProcess()->GetCells()) {
    // added_cell->Color(State::Alive);
    // }
    player_->AddShip();
    player_->FinishSettingShip();
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
    return cell->state != State::Clear;
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

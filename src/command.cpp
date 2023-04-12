#include "../lib/command.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/game.hpp"
#include "../lib/player.hpp"
#include "../lib/window.hpp"

GameLoop* Command::loop_ = nullptr;

Command::Command() : type_(Event::Count) {}

Command::Command(const Event::EventType& type) : type_(type) {}

const Event::EventType& Command::GetType() { return type_; }

SetButtonsCommand::SetButtonsCommand(map<string, Button*>* buttons)
    : buttons_(buttons) {}

bool SetButtonsCommand::Execute() { loop_->window_.SetButtons(buttons_);
  return true;
}

template <typename Type>
ExecCommand<Type>::ExecCommand(Type* obj, const Event::EventType& type,
                               void (*func)(Type* obj))
    : Command(type), obj_(obj), func_(func) {}

template <typename Type>
bool ExecCommand<Type>::Execute() {
  (*func_)(obj_);
  return true;
}

CellCommand::CellCommand(Player* player, Cell* cell)
    : player_(player), cell_(cell) {}

AddCellCommand::AddCellCommand(Player* player, Cell* cell)
    : CellCommand(player, cell) {}

bool AddCellCommand::Execute() {
  bool valid = IsValid();
  if (valid) {
    if (cell_->GetState() == State::Clear) {
      player_->ship_in_process_.AddCell(cell_);
    } else {
      player_->ship_in_process_.EraseCell(cell_);
    }
    loop_->buttons_["select_" + std::to_string(player_->GetIndex())]["errcell"]
        ->SetShow(false);
    loop_->buttons_["select_" + std::to_string(player_->GetIndex())]["errship"]
        ->SetShow(false);
  } else {
    loop_->buttons_["select_" + std::to_string(player_->GetIndex())]["ok"]
        ->SetShow(false);
    loop_->buttons_["select_" + std::to_string(player_->GetIndex())]["errcell"]
        ->SetShow(true);
  }
  loop_->window_.DrawObjects();
  return valid;
}

bool AddCellCommand::IsValid() const {
  return cell_->GetState() == State::Clear ||
         cell_->GetState() == State::Chosen;
}

AddShipCommand::AddShipCommand(Player* player) : player_(player) {}

bool AddShipCommand::Execute() {
  bool valid = IsValid();
  if (valid) {
    player_->AddShip();
    loop_->buttons_["select_" + std::to_string(player_->GetIndex())]["errcell"]
        ->SetShow(false);
    loop_->buttons_["select_" + std::to_string(player_->GetIndex())]["errship"]
        ->SetShow(false);
    loop_->buttons_["select_" + std::to_string(player_->GetIndex())]["ok"]
        ->SetShow(true);
    if (player_->GetShipCount() == loop_->kShips) {
      if (player_->GetIndex() == 0) {
        loop_->window_.SetButtons(&loop_->buttons_["select_1"]);
      } else {
        loop_->window_.SetButtons(&loop_->buttons_["starts"]);
        sf::sleep(sf::milliseconds(1000));
        loop_->window_.SetButtons(&loop_->buttons_["play_0"]);
      }
    }
  } else {
    loop_->buttons_["select_" + std::to_string(player_->GetIndex())]["ok"]
        ->SetShow(false);
    loop_->buttons_["select_" + std::to_string(player_->GetIndex())]["errship"]
        ->SetShow(true);
  }
  loop_->window_.DrawObjects();
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
  return true;
}

ShootCommand::ShootCommand(Player* player, Cell* cell)
    : CellCommand(player, cell) {}

bool ShootCommand::Execute() {
  bool valid = IsValid();
  if (valid) {
    ShotResult shot_result;
    player_->Shoot(cell_, shot_result);
    if (player_->GetRival()->GetShipCount() == 0) {
      std::cout << "Player " << player_->GetIndex() << " won.\n";
      std::cout.flush();
    }
    if (player_->GetLastShotResult() == ShotResult::Miss) {
      loop_->window_.SetButtons(
          &loop_->buttons_["play_" + std::to_string(1 - player_->GetIndex())]);
    }
  }
  loop_->window_.DrawObjects();
  return valid;
}

bool ShootCommand::IsValid() const { return true; }

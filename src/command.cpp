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

SetButtonsCommand::SetButtonsCommand(const string& str) : str_(str) {}

bool SetButtonsCommand::Execute() {
  if(str_ == "menu") {
    loop_->Clear();
  }
  loop_->GetWindow()->SetButtons(str_);
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
  Send();
  bool valid = IsValid();
  string scene = "select_" + std::to_string(player_->GetIndex());
  if (valid) {
    if (cell_->GetState() == State::Clear) {
      player_->ship_in_process_.AddCell(cell_);
    } else {
      player_->ship_in_process_.EraseCell(cell_);
    }
    loop_->GetWindow()->SetShow(scene, "errcell", false);
    loop_->GetWindow()->SetShow(scene, "errship", false);
  } else {
    loop_->GetWindow()->SetShow(scene, "ok", false);
    loop_->GetWindow()->SetShow(scene, "errcell", true);
  }
  loop_->GetWindow()->DrawObjects();
  return valid;
}

bool AddCellCommand::IsValid() const {
  return cell_->GetState() == State::Clear ||
         cell_->GetState() == State::Chosen;
}

void AddCellCommand::Send() {
  loop_->GetNetwork()->Send("add_cell", std::to_string(cell_->GetCoord().x * loop_->GetSize().y + cell_->GetCoord().y));
}

AddShipCommand::AddShipCommand(Player* player) : player_(player) {}

bool AddShipCommand::Execute() {
  Send();
  bool valid = IsValid();
  string scene = "select_" + std::to_string(player_->GetIndex());
  if (valid) {
    player_->AddShip();
    loop_->GetWindow()->SetShow(scene, "errcell", false);
    loop_->GetWindow()->SetShow(scene, "errship", false);
    loop_->GetWindow()->SetShow(scene, "ok", true);
    loop_->GetWindow()->DrawObjects();
    sf::sleep(sf::milliseconds(500));
    if (player_->GetShipCount() == loop_->kShips) {
      loop_->SwitchBlock();
      player_->GetField()->RemoveProhibited();
      if (player_->GetIndex() == 0) {
        loop_->GetWindow()->SetButtons("shift_select");
        sf::sleep(sf::milliseconds(2000));
        loop_->GetWindow()->SetButtons("select_1");
      } else {
        loop_->GetWindow()->SetButtons("starts");
        sf::sleep(sf::milliseconds(2000));
        loop_->GetWindow()->SetButtons("turn_" +
                                       std::to_string(0));
        sf::sleep(sf::milliseconds(2000));
        loop_->GetWindow()->SetButtons("play_0");
      }
    }
  } else {
    loop_->GetWindow()->SetShow(scene, "ok", false);
    loop_->GetWindow()->SetShow(scene, "errship", true);
  }
  loop_->GetWindow()->DrawObjects();
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

void AddShipCommand::Send() {
  loop_->GetNetwork()->Send("add_ship");
}

ShootCommand::ShootCommand(Player* player, Cell* cell)
    : CellCommand(player, cell) {}

bool ShootCommand::Execute() {
  Send();
  bool valid = IsValid();
  if (valid) {
    ShotResult shot_result;
    player_->Shoot(cell_, shot_result);
    if (player_->GetRival()->GetShipCount() == 0) {
      loop_->GetWindow()->SetButtons("won_" +
                                     std::to_string(player_->GetIndex()));
      loop_->Unblock();
    }
    if (player_->GetLastShotResult() == ShotResult::Miss) {
      loop_->GetWindow()->SetButtons("turn_" +
                                     std::to_string(1 - player_->GetIndex()));
      sf::sleep(sf::milliseconds(2000));
      loop_->GetWindow()->SetButtons("play_" +
                                     std::to_string(1 - player_->GetIndex()));
      loop_->SwitchBlock();
    }
  }
  loop_->GetWindow()->DrawObjects();
  return valid;
}

bool ShootCommand::IsValid() const { return true; }

void ShootCommand::Send() {
  loop_->GetNetwork()->Send("shoot", std::to_string(cell_->GetCoord().x * loop_->GetSize().y + cell_->GetCoord().y));
}

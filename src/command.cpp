#include "../lib/command.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/player.hpp"
#include "../lib/window.hpp"

Command::Command() : type_(Event::Count) {}

Command::Command(const Event::EventType& type) : type_(type) {}

const Event::EventType& Command::GetType() { return type_; }

template <typename Type>
ExecCommand<Type>::ExecCommand() : Command(), obj_(nullptr), func_(Empty) {}

template <typename Type>
ExecCommand<Type>::ExecCommand(Type* obj, const Event::EventType& type,
                               void (*func)(Type* obj))
    : Command(type), obj_(obj), func_(func) {}

template <typename Type>
bool ExecCommand<Type>::Execute() {
  bool valid = IsValid();
  if (valid) {
    (*func_)(obj_);
  }
  return valid;
}

template <typename Type>
bool ExecCommand<Type>::IsValid() const {
  return *func_ != nullptr;
}

template <typename Type>
void ExecCommand<Type>::Empty(Type* val) {}

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
  }
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

ShootCommand::ShootCommand(Player* player, Cell* cell)
    : CellCommand(player, cell) {}

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

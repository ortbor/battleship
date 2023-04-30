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

SetCommand::SetCommand(const string& str) : str_(str) {}

bool SetCommand::Execute() {
  if (str_ == "menu") {
    loop_->Clear();
  }
  loop_->GetWindow().SetButtons(str_);
  return true;
}

bool AddSymbolCommand::Execute() {
  loop_->GetWindow().SetShow("ip", "status", 1, false);
  loop_->GetWindow().SetShow("ip", "status", 2, false);

  size_t code = loop_->GetWindow().GetEvent().text.unicode;

  if (code == 8 && !loop_->GetWindow().GetBox().empty()) {
    loop_->GetWindow().GetBox().pop_back();
  } else if (code == 13) {
    ClientCommand().Execute();
  } else if (code >= 46 && code <= 58 && code != 47 &&
             loop_->GetWindow().GetBox().size() < 21) {
    loop_->GetWindow().GetBox().push_back(static_cast<char>(code));
  }
  loop_->GetWindow().SetObject("ip", "box", 1, loop_->GetWindow().GetBox());
  return true;
}

std::string SaveIPCommand::ip_num_r =
    R"(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]))";
std::string SaveIPCommand::ip_port_r =
    R"(([0-9]|[1-9][0-9]{1,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5]))";
std::string SaveIPCommand::ip_str_r =
    R"(^()" + ip_num_r + R"(\.){3})" + ip_num_r + R"(:)" + ip_port_r;
std::regex SaveIPCommand::ip_regex(SaveIPCommand::ip_str_r);

bool SaveIPCommand::Execute() {
  string text = loop_->GetWindow().GetBox();
  if (!std::regex_match(text, ip_regex)) {
    loop_->GetWindow().SetShow("ip", "status", 1, true);
    return false;
  }

  string ip_address;
  while (text[0] != ':') {
    ip_address.push_back(text[0]);
    text.erase(text.begin());
  }
  text.erase(text.begin());
  if (loop_->GetNetwork()->ClientConnect(ip_address, std::stoi(text)) !=
      Socket::Status::Done) {
    loop_->GetWindow().SetShow("ip", "status", 2, true);
    return false;
  }
  loop_->GetWindow().GetBox().clear();
  loop_->GetWindow().SetShow("ip", "status", 0, true);
  sf::sleep(sf::milliseconds(1000));

  if (loop_->GetLocalPlayer() == 1) {
    loop_->Block();
  }
  loop_->GetWindow().SetButtons("select_0");
  return true;
}

ExecCommand::ExecCommand(GameWindow& obj, const Event::EventType& type,
                         void (*func)(GameWindow& obj))
    : Command(type), obj_(obj), func_(func) {}

bool ExecCommand::Execute() {
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
  loop_->GetWindow().SetShow(scene, "status", 0, false);
  loop_->GetWindow().SetShow(scene, "status", 2, false);
  if (valid) {
    if (cell_->GetState() == State::Clear) {
      player_->ship_in_process_.AddCell(cell_);
    } else {
      player_->ship_in_process_.EraseCell(cell_);
    }
    loop_->GetWindow().SetShow(scene, "status", 1, false);
  } else {
    loop_->GetWindow().SetShow(scene, "status", 1, true);
  }
  return valid;
}

bool AddCellCommand::IsValid() const {
  if (loop_->IsBlocked()) {
    return false;
  }
  return cell_->GetState() == State::Clear ||
         cell_->GetState() == State::Chosen;
}

void AddCellCommand::Send() {
  loop_->GetNetwork()->Send(
      "add_cell", std::to_string(cell_->GetCoord().x * loop_->GetSize().y +
                                 cell_->GetCoord().y));
}

AddShipCommand::AddShipCommand(Player* player) : player_(player) {}

bool AddShipCommand::Execute() {
  Send();
  bool valid = IsValid();
  string scene = "select_" + std::to_string(player_->GetIndex());
  loop_->GetWindow().SetShow(scene, "status", 1, false);
  if (valid) {
    player_->AddShip();
    loop_->GetWindow().SetShow(scene, "status", 0, true);
    loop_->GetWindow().SetShow(scene, "status", 2, false);
    loop_->GetWindow().DrawObjects();
    sf::sleep(sf::milliseconds(1000));
    if (player_->GetShipCount() == loop_->kShips) {
      loop_->SwitchBlock();
      player_->GetField()->RemoveProhibited();
      if (player_->GetIndex() == 0) {
        loop_->GetWindow().SetButtons("select_1");
      } else {
        loop_->GetWindow().GetMusic("main").stop();
        loop_->GetWindow().GetMusic("game").play();
        loop_->GetWindow().SetButtons("play_0");
      }
    }
  } else {
    loop_->GetWindow().SetShow(scene, "status", 0, false);
    loop_->GetWindow().SetShow(scene, "status", 2, true);
  }
  return valid;
}

bool AddShipCommand::IsValid() const {
  if (loop_->IsBlocked() || !player_->GetShipInProcess()->IsClassic()) {
    return false;
  }
  return player_->GetNumberOfShipsSized(
             player_->GetShipInProcess()->GetSize()) <
         5 - player_->GetShipInProcess()->GetSize();
}

void AddShipCommand::Send() { loop_->GetNetwork()->Send("add_ship"); }

ShootCommand::ShootCommand(Player* player, Cell* cell)
    : CellCommand(player, cell) {}

bool ShootCommand::Execute() {
  Send();
  bool valid = IsValid();
  if (valid) {
    ShotResult shot_result;
    player_->Shoot(cell_, shot_result);
    if (player_->GetRival()->GetShipCount() == 0) {
      loop_->GetWindow().SetButtons("won_" +
                                    std::to_string(player_->GetIndex()));
      loop_->Unblock();
    }
    if (player_->GetLastShotResult() == ShotResult::Miss) {
      loop_->GetWindow().SetButtons("turn_" +
                                    std::to_string(1 - player_->GetIndex()));
      sf::sleep(sf::milliseconds(2000));
      loop_->GetWindow().SetButtons("play_" +
                                    std::to_string(1 - player_->GetIndex()));
      loop_->SwitchBlock();
    }
  }
  return valid;
}

bool ShootCommand::IsValid() const { return !loop_->IsBlocked(); }

void ShootCommand::Send() {
  loop_->GetNetwork()->Send(
      "shoot", std::to_string(cell_->GetCoord().x * loop_->GetSize().y +
                              cell_->GetCoord().y));
}

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

void SetCommand::Execute() {
  if (str_ == "menu") {
    loop_->Clear();
  }
  loop_->GetWnd().SetButtons(str_);
}

void IPBoxCommand::Execute() {
  loop_->GetWnd().SetShow("ip", "status", 1, false);
  loop_->GetWnd().SetShow("ip", "status", 2, false);
  loop_->GetWnd().SetShow("ip", "status", 3, false);

  size_t code = loop_->GetWnd().GetEvent().text.unicode;

  if (code == 8 && !loop_->GetWnd().GetBox().empty()) {
    loop_->GetWnd().GetBox().pop_back();
  } else if (code == 13) {
    ClientCommand().Execute();
  } else if (code >= 46 && code <= 58 && code != 47 &&
             loop_->GetWnd().GetBox().size() < 21) {
    loop_->GetWnd().GetBox().push_back(static_cast<char>(code));
  }
  loop_->GetWnd().SetObject("ip", "box", 1, loop_->GetWnd().GetBox());
}

std::string SaveIPCommand::ip_num_r =
    R"(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]))";
std::string SaveIPCommand::ip_port_r =
    R"(([0-9]|[1-9][0-9]{1,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5]))";
std::string SaveIPCommand::ip_str_r =
    R"(^()" + ip_num_r + R"(\.){3})" + ip_num_r + R"(:)" + ip_port_r;
std::regex SaveIPCommand::ip_regex(SaveIPCommand::ip_str_r);

void ServerCommand::Execute() {
  loop_->GetWnd().SetButtons("waiting");
  loop_->GetNetwork().ServerConnect();
}

void ClientCommand::Execute() {
  loop_->GetWnd().SetShow("ip", "status", 2, false);
  loop_->GetWnd().SetShow("ip", "status", 3, false);

  switch (loop_->GetNetwork().ClientConnect(ParseIp())) {
    case Socket::Status::Done:
      loop_->GetWnd().SetShow("ip", "status", 0, true);
      sf::sleep(sf::milliseconds(1000));
      loop_->LaunckNetwork();
      loop_->GetWnd().GetBox().clear();
      loop_->GetWnd().SetButtons("select_0");
      break;
    case Socket::Status::Disconnected:
      loop_->GetWnd().SetShow("ip", "status", 2, true);
      break;
    default:
      loop_->GetWnd().SetShow("ip", "status", 3, true);
  }
}

void TerminateCommand::Execute() {
  loop_->GetNetwork().Terminate();
  loop_->Terminate();
  loop_->GetWnd().SetButtons("play");
}

pair<string, size_t> ClientCommand::ParseIp() {
  string text = loop_->GetWnd().GetBox();
  if (!std::regex_match(text, ip_regex)) {
    loop_->GetWnd().SetShow("ip", "status", 1, true);
    return {"", 0};
  }

  string ip_address;
  while (text[0] != ':') {
    ip_address.push_back(text[0]);
    text.erase(text.begin());
  }
  text.erase(text.begin());
  return {ip_address, std::stoi(text)};
}

ExecCommand::ExecCommand(GameWindow& obj, const Event::EventType& type,
                         void (*func)(GameWindow& obj))
    : Command(type), obj_(obj), func_(func) {}

void ExecCommand::Execute() { (*func_)(obj_); }

CellCommand::CellCommand(Player* player, Cell* cell)
    : player_(player), cell_(cell) {}

AddCellCommand::AddCellCommand(Player* player, Cell* cell)
    : CellCommand(player, cell) {}

void AddCellCommand::Execute() {
  Send();
  string scene = "select_" + std::to_string(player_->GetIndex());
  loop_->GetWnd().SetShow(scene, "status", 0, false);
  loop_->GetWnd().SetShow(scene, "status", 2, false);

  if (!IsValid()) {
    loop_->GetWnd().SetShow(scene, "status", 1, true);
    return;
  }
  if (cell_->GetState() == State::Clear) {
    player_->ship_in_process_.AddCell(cell_);
  } else {
    player_->ship_in_process_.EraseCell(cell_);
  }
  loop_->GetWnd().SetShow(scene, "status", 1, false);
}

bool AddCellCommand::IsValid() const {
  if (loop_->Blocked()) {
    return false;
  }
  return cell_->GetState() == State::Clear ||
         cell_->GetState() == State::Chosen;
}

void AddCellCommand::Send() {
  size_t index = cell_->GetCoord().x * loop_->GetSize().y + cell_->GetCoord().y;
  loop_->GetNetwork().Send("add_cell", std::to_string(index));
}

AddShipCommand::AddShipCommand(Player* player) : player_(player) {}

void AddShipCommand::Execute() {
  Send();
  string scene = "select_" + std::to_string(player_->GetIndex());
  loop_->GetWnd().SetShow(scene, "status", 1, false);

  if (!IsValid()) {
    loop_->GetWnd().SetShow(scene, "status", 0, false);
    loop_->GetWnd().SetShow(scene, "status", 2, true);
    return;
  }
  player_->AddShip();
  loop_->GetWnd().SetShow(scene, "status", 0, true);
  loop_->GetWnd().SetShow(scene, "status", 2, false);
  loop_->GetWnd().DrawObjects();
  sf::sleep(sf::milliseconds(1000));
  if (player_->GetShipCount() == loop_->kShips) {
    loop_->Blocked() = !loop_->Blocked();
    player_->GetField()->RemoveProhibited();
    if (player_->GetIndex() == 0) {
      loop_->GetWnd().SetButtons("select_1");
    } else {
      loop_->GetWnd().GetMusic("main").stop();
      loop_->GetWnd().GetMusic("game").play();
      loop_->GetWnd().SetButtons("play_0");
    }
  }
}

bool AddShipCommand::IsValid() const {
  if (loop_->Blocked() || !player_->GetShipInProcess()->IsClassic()) {
    return false;
  }
  return player_->GetNumberOfShips(player_->GetShipInProcess()->GetSize()) <
         5 - player_->GetShipInProcess()->GetSize();
}

void AddShipCommand::Send() { loop_->GetNetwork().Send("add_ship"); }

ShootCommand::ShootCommand(Player* player, Cell* cell)
    : CellCommand(player, cell) {}

void ShootCommand::Execute() {
  Send();
  if (!IsValid()) {
    return;
  }

  size_t index = player_->GetIndex();
  ShotResult shot_result;
  player_->Shoot(cell_, shot_result);
  if (player_->GetRival()->GetShipCount() == 0) {
    loop_->GetWnd().SetButtons("won_" + std::to_string(index));
    loop_->Blocked() = false;
  }
  if (player_->GetLastShotResult() == ShotResult::Miss) {
    loop_->GetWnd().SetButtons("turn_" + std::to_string(1 - index));
    sf::sleep(sf::milliseconds(2000));
    loop_->GetWnd().SetButtons("play_" + std::to_string(1 - index));
    loop_->Blocked() = !loop_->Blocked();
  }
}

bool ShootCommand::IsValid() const { return !loop_->Blocked(); }

void ShootCommand::Send() {
  size_t index = cell_->GetCoord().x * loop_->GetSize().y + cell_->GetCoord().y;
  loop_->GetNetwork().Send("shoot", std::to_string(index));
}

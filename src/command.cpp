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

<<<<<<< HEAD
void IPBoxCommand::Execute(bool is_remote) {
  m_loop->GetWnd().SetShow("client", "status", 1, false);
  m_loop->GetWnd().SetShow("client", "status", 2, false);
  m_loop->GetWnd().SetShow("client", "status", 3, false);
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
void IPBoxCommand::Execute() {
  m_loop->GetWnd().SetShow("client", "status", 1, false);
  m_loop->GetWnd().SetShow("client", "status", 2, false);
  m_loop->GetWnd().SetShow("client", "status", 3, false);
=======
void IPBoxCommand::Execute() {
  loop_->GetWnd().SetShow("ip", "status", 1, false);
  loop_->GetWnd().SetShow("ip", "status", 2, false);
  loop_->GetWnd().SetShow("ip", "status", 3, false);
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)

  size_t code = loop_->GetWnd().GetEvent().text.unicode;

  if (code == 8 && !loop_->GetWnd().GetBox().empty()) {
    loop_->GetWnd().GetBox().pop_back();
  } else if (code == 13) {
    ClientCommand().Execute();
  } else if (code >= 46 && code <= 58 && code != 47 &&
             loop_->GetWnd().GetBox().size() < 21) {
    loop_->GetWnd().GetBox().push_back(static_cast<char>(code));
  }
<<<<<<< HEAD
  m_loop->GetWnd().SetObject("client", "box", 1,
                             m_loop->GetWnd().GetBoxes()["ip"]);
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
  m_loop->GetWnd().SetObject("client", "box", 1,
                            m_loop->GetWnd().GetBoxes()["ip"]);
=======
  loop_->GetWnd().SetObject("ip", "box", 1, loop_->GetWnd().GetBox());
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)
}

<<<<<<< HEAD
void PortBoxCommand::Execute(bool is_remote) {
  m_loop->GetWnd().SetShow("settings", "port_status", 1, false);
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
void PortBoxCommand::Execute() {
  m_loop->GetWnd().SetShow("settings", "port_status", 1, false);
=======
void PortBoxCommand::Execute() {
  loop_->GetWnd().SetShow("settings", "status", 1, false);
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)

  size_t code = loop_->GetWnd().GetEvent().text.unicode;

  if (code == 8 && !loop_->GetWnd().GetBox().empty()) {
    loop_->GetWnd().GetBox().pop_back();
  } else if (code == 13) {
    SavePortCommand().Execute();
  } else if (code >= 48 && code <= 58 && loop_->GetWnd().GetBox().size() < 5) {
    loop_->GetWnd().GetBox().push_back(static_cast<char>(code));
  }
<<<<<<< HEAD
  m_loop->GetWnd().SetObject("settings", "port_box", 1,
                             m_loop->GetWnd().GetBoxes()["port"]);
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
  m_loop->GetWnd().SetObject("settings", "port_box", 1,
                            m_loop->GetWnd().GetBoxes()["port"]);
=======
  loop_->GetWnd().SetObject("settings", "box", 1, loop_->GetWnd().GetBox());
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)
}

std::string SaveIPCommand::ip_num_r =
    R"(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]))";
std::string SaveIPCommand::ip_port_r =
    R"(([0-9]|[1-9][0-9]{1,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5]))";
<<<<<<< HEAD
std::string IPClientCommand::m_ip_full =
    R"(^()" + m_ip_addr + R"(\.){3})" + m_ip_addr + R"(:)" + m_ip_port;
std::regex IPClientCommand::m_ip_regex(IPClientCommand::m_ip_full);
std::regex PortCommand::m_port_regex(IPClientCommand::m_ip_port);
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
std::string IPClientCommand::m_ip_full =
    R"(^()" + m_ip_addr + R"(\.){3})" + m_ip_addr + R"(:)" + m_ip_port;
std::regex IPClientCommand::m_ip_regex(IPClientCommand::m_ip_port);
std::regex PortCommand::m_port_regex(IPClientCommand::m_ip_port);
=======
std::string SaveIPCommand::ip_str_r =
    R"(^()" + ip_num_r + R"(\.){3})" + ip_num_r + R"(:)" + ip_port_r;
std::regex SaveIPCommand::ip_regex(SaveIPCommand::ip_str_r);
std::regex SavePortCommand::port_regex(
    R"(([0-9]|[1-9][0-9]{1,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5]))");
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)

<<<<<<< HEAD
void IPClientCommand::Execute(bool is_remote) {
  m_loop->Blocked() = false;
  m_loop->SetLocalPlayer(0);
  m_loop->GetWnd().SetShow("client", "status", 2, false);
  m_loop->GetWnd().SetShow("client", "status", 3, false);
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
void IPClientCommand::Execute() {
  m_loop->GetWnd().SetShow("client", "status", 2, false);
  m_loop->GetWnd().SetShow("client", "status", 3, false);
=======
void ServerCommand::Execute() {
  loop_->GetWnd().SetButtons("waiting");
  loop_->GetNetwork().ServerConnect();
}
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)

void ClientCommand::Execute() {
  loop_->GetWnd().SetShow("ip", "status", 2, false);
  loop_->GetWnd().SetShow("ip", "status", 3, false);

  switch (loop_->GetNetwork().ClientConnect(ParseIp())) {
    case Socket::Done:
      loop_->GetWnd().SetShow("ip", "status", 0, true);
      sf::sleep(sf::milliseconds(1000));
      loop_->LaunckNetwork();
      loop_->GetWnd().GetBox().clear();
      loop_->GetWnd().SetButtons("select_0");
      break;
    case Socket::Disconnected:
      loop_->GetWnd().SetShow("ip", "status", 2, true);
      break;
    default:
      loop_->GetWnd().SetShow("ip", "status", 3, true);
  }
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

<<<<<<< HEAD
void IPServerCommand::Execute(bool is_remote) {
  m_loop->Blocked() = true;
  m_loop->SetLocalPlayer(1);
  m_loop->GetWnd().SetButtons("server");
  m_loop->GetNetwork().ServerConnect();
}

void PortCommand::Execute(bool is_remote) {
  m_loop->GetWnd().SetShow("settings", "port_status", 1, false);
  m_loop->GetWnd().SetShow("settings", "port_status", 2, false);

  string text = m_loop->GetWnd().GetBoxes()["port"];
  if (!std::regex_match(text, m_port_regex)) {
    m_loop->GetWnd().SetShow("settings", "port_status", 1, true);
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
void IPServerCommand::Execute() {
  m_loop->GetWnd().SetButtons("server");
  m_loop->GetNetwork().ServerConnect();
}

void PortCommand::Execute() {
  m_loop->GetWnd().SetShow("settings", "port_status", 1, false);
  m_loop->GetWnd().SetShow("settings", "port_status", 2, false);

  string text = m_loop->GetWnd().GetBoxes()["port"];
  if (!std::regex_match(text, m_port_regex)) {
    m_loop->GetWnd().SetShow("settings", "port_status", 1, true);
=======
void SavePortCommand::Execute() {
  loop_->GetWnd().SetShow("settings", "status", 1, false);
  loop_->GetWnd().SetShow("settings", "status", 2, false);
  
  string text = loop_->GetWnd().GetBox();
  if (!std::regex_match(text, port_regex)) {
    loop_->GetWnd().SetShow("settings", "status", 1, true);
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)
    return;
  }

  switch (loop_->GetNetwork().UpdatePort(std::stoi(text))) {
    case Socket::Done:
      loop_->GetWnd().SetShow("settings", "status", 0, true);
      sf::sleep(sf::milliseconds(1000));
      loop_->GetWnd().SetShow("settings", "status", 0, false);
      break;
    default:
      loop_->GetWnd().SetShow("settings", "status", 2, true);
  }
}

<<<<<<< HEAD
void TerminateCommand::Execute(bool is_remote) {
  m_loop->GetNetwork().Terminate();
  m_loop->Terminate();
  m_loop->GetWnd().SetButtons("play");
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
void TerminateCommand::Execute() {
  m_loop->GetNetwork().Terminate();
  m_loop->Terminate();
  m_loop->GetWnd().SetButtons("play");
=======
void TerminateCommand::Execute() {
  loop_->GetNetwork().Terminate();
  loop_->Terminate();
  loop_->GetWnd().SetButtons("play");
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)
}

ExecCommand::ExecCommand(GameWindow& obj, const Event::EventType& type,
                         void (*func)(GameWindow& obj))
    : Command(type), obj_(obj), func_(func) {}

<<<<<<< HEAD
void WindowCommand::Execute(bool is_remote) {
  switch (m_request) {
    case CMDType::Close:
      m_loop->GetWnd().close();
      m_loop->Terminate();
      break;

    case CMDType::Ficha:
      m_loop->GetWnd().Ficha();
      break;
  }
}

VolumeCommand::VolumeCommand(CMDVolume type) : m_type(type) {}

void VolumeCommand::Execute(bool is_remote) {
  m_loop->GetWnd().SetVolume(m_type);
}

SetSceneCommand::SetSceneCommand(const string& str) : m_str(str) {}

void SetSceneCommand::Execute(bool is_remote) {
  if (m_str == "menu") {
    m_loop->Clear();
  } else if (m_str == "settings") {
    m_loop->GetWnd().GetBoxes()["ip"] =
        bs::atos(m_loop->GetNetwork().GetPort());
    m_loop->GetWnd().SetObject("settings", "port_box", 1,
                               m_loop->GetWnd().GetBoxes()["ip"]);
  }
  m_loop->GetWnd().SetButtons(m_str);
}
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
void WindowCommand::Execute() {
  switch (m_request) {
    case CMDType::Close:
      m_loop->GetWnd().close();
      m_loop->Terminate();
      break;

    case CMDType::Ficha:
      m_loop->GetWnd().Ficha();
      break;
  }
}

VolumeCommand::VolumeCommand(CMDVolume type) : m_type(type) {}

void VolumeCommand::Execute() { m_loop->GetWnd().SetVolume(m_type); }

SetSceneCommand::SetSceneCommand(const string& str) : str_(str) {}

void SetSceneCommand::Execute() {
  if (str_ == "menu") {
    m_loop->Clear();
  } else if (str_ == "settings") {
    m_loop->GetWnd().GetBoxes()["ip"] = bs::atos(m_loop->GetNetwork().GetPort());
    m_loop->GetWnd().SetObject("settings", "port_box", 1,
                              m_loop->GetWnd().GetBoxes()["ip"]);
  }
  m_loop->GetWnd().SetButtons(str_);
}
=======
void ExecCommand::Execute() { (*func_)(obj_); }
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)

CellCommand::CellCommand(Player* player, Cell* cell)
    : player_(player), cell_(cell) {}

AddCellCommand::AddCellCommand(Player* player, Cell* cell)
    : CellCommand(player, cell) {
  std::cout << "executing\n";
  std::cout.flush();
}

<<<<<<< HEAD
void AddCellCommand::Execute(bool is_remote) {
  string scene = "select_" + std::to_string(m_player->GetIndex());
  m_loop->GetWnd().SetShow(scene, "status", 0, false);
  m_loop->GetWnd().SetShow(scene, "status", 2, false);
  std::cout << "fuuck\n";
  std::cout.flush();
  if ((!is_remote && m_loop->Blocked()) || !IsValid()) {
    m_loop->GetWnd().SetShow(scene, "status", 1, true);
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
void AddCellCommand::Execute() {
  Send();
  string scene = "select_" + std::to_string(m_player->GetIndex());
  m_loop->GetWnd().SetShow(scene, "status", 0, false);
  m_loop->GetWnd().SetShow(scene, "status", 2, false);

  if (!IsValid()) {
    m_loop->GetWnd().SetShow(scene, "status", 1, true);
=======
void AddCellCommand::Execute() {
  Send();
  string scene = "select_" + std::to_string(player_->GetIndex());
  loop_->GetWnd().SetShow(scene, "status", 0, false);
  loop_->GetWnd().SetShow(scene, "status", 2, false);

  if (!IsValid()) {
    loop_->GetWnd().SetShow(scene, "status", 1, true);
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)
    return;
  }
<<<<<<< HEAD
  if (!is_remote) {
    Send();
  }

  std::cout << "executing3\n";
  std::cout.flush();
  if (m_cell->GetState() == CellState::Clear) {
    m_player->m_ship_in_process.AddCell(m_cell);
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
  if (m_cell->GetState() == CellState::Clear) {
    m_player->m_ship_in_process.AddCell(m_cell);
=======
  if (cell_->GetState() == State::Clear) {
    player_->ship_in_process_.AddCell(cell_);
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)
  } else {
    player_->ship_in_process_.EraseCell(cell_);
  }
<<<<<<< HEAD
  m_loop->GetWnd().SetShow(scene, "status", 1, false);
  std::cout << "executing4\n";
  std::cout.flush();
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
  m_loop->GetWnd().SetShow(scene, "status", 1, false);
=======
  loop_->GetWnd().SetShow(scene, "status", 1, false);
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)
}

bool AddCellCommand::IsValid() const {
<<<<<<< HEAD
  return m_cell->GetState() == CellState::Clear ||
         m_cell->GetState() == CellState::Chosen;
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
  if (m_loop->Blocked()) {
    return false;
  }
  return m_cell->GetState() == CellState::Clear ||
         m_cell->GetState() == CellState::Chosen;
=======
  if (loop_->Blocked()) {
    return false;
  }
  return cell_->GetState() == State::Clear ||
         cell_->GetState() == State::Chosen;
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)
}

void AddCellCommand::Send() {
<<<<<<< HEAD
  size_t index =
      m_cell->GetCoord().x * m_loop->GetSize().y + m_cell->GetCoord().y;
  m_loop->GetNetwork().Send("add_cell", std::to_string(index));
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
  size_t index = m_cell->GetCoord().x * m_loop->GetSize().y + m_cell->GetCoord().y;
  m_loop->GetNetwork().Send("add_cell", std::to_string(index));
=======
  size_t index = cell_->GetCoord().x * loop_->GetSize().y + cell_->GetCoord().y;
  loop_->GetNetwork().Send("add_cell", std::to_string(index));
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)
}

AddShipCommand::AddShipCommand(Player* player) : player_(player) {}

<<<<<<< HEAD
void AddShipCommand::Execute(bool is_remote) {
  string scene = "select_" + std::to_string(m_player->GetIndex());
  m_loop->GetWnd().SetShow(scene, "status", 1, false);
  if ((!is_remote && m_loop->Blocked()) || !IsValid()) {
    std::cout << "blocked(\n";
    std::cout.flush();
    m_loop->GetWnd().SetShow(scene, "status", 0, false);
    m_loop->GetWnd().SetShow(scene, "status", 2, true);
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
void AddShipCommand::Execute() {
  Send();
  string scene = "select_" + std::to_string(m_player->GetIndex());
  m_loop->GetWnd().SetShow(scene, "status", 1, false);

  if (!IsValid()) {
    m_loop->GetWnd().SetShow(scene, "status", 0, false);
    m_loop->GetWnd().SetShow(scene, "status", 2, true);
=======
void AddShipCommand::Execute() {
  Send();
  string scene = "select_" + std::to_string(player_->GetIndex());
  loop_->GetWnd().SetShow(scene, "status", 1, false);

  if (!IsValid()) {
    loop_->GetWnd().SetShow(scene, "status", 0, false);
    loop_->GetWnd().SetShow(scene, "status", 2, true);
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)
    return;
  }
<<<<<<< HEAD
  if (!is_remote) {
    Send();
  }

  m_player->AddShip();
  m_loop->GetWnd().SetShow(scene, "status", 0, true);
  m_loop->GetWnd().SetShow(scene, "status", 2, false);
  m_loop->GetWnd().DrawObjects();
  sf::sleep(sf::milliseconds(1000));
  std::cout << "shipcounts " << m_player->GetShipCount() << " "
            << m_loop->kShips << "\n";
  if (m_player->GetShipCount() == m_loop->kShips) {
    m_loop->Blocked() = !m_loop->Blocked();
    std::cout << "here " << m_loop->Blocked() << "\n";
    std::cout.flush();
    m_player->GetMField()->RemoveProhibited();
    if (m_player->GetIndex() == 0) {
      m_loop->GetWnd().SetButtons("select_1");
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
  m_player->AddShip();
  m_loop->GetWnd().SetShow(scene, "status", 0, true);
  m_loop->GetWnd().SetShow(scene, "status", 2, false);
  m_loop->GetWnd().DrawObjects();
  sf::sleep(sf::milliseconds(kMoveSleep));
  if (m_player->GetShipCount() == m_loop->kShips) {
    m_loop->Blocked() = !m_loop->Blocked();
    m_player->GetMField()->RemoveProhibited();
    if (m_player->GetIndex() == 0) {
      m_loop->GetWnd().SetButtons("select_1");
=======
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
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)
    } else {
      loop_->GetWnd().GetMusic("main").stop();
      loop_->GetWnd().GetMusic("game").play();
      loop_->GetWnd().SetButtons("play_0");
    }
  }
}

bool AddShipCommand::IsValid() const {
<<<<<<< HEAD
  if (!m_player->GetShipInProcess()->IsClassic()) {
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
  if (m_loop->Blocked() || !m_player->GetShipInProcess()->IsClassic()) {
=======
  if (loop_->Blocked() || !player_->GetShipInProcess()->IsClassic()) {
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)
    return false;
  }
  return player_->GetNumberOfShips(player_->GetShipInProcess()->GetSize()) <
         5 - player_->GetShipInProcess()->GetSize();
}

void AddShipCommand::Send() { loop_->GetNetwork().Send("add_ship"); }

ShootCommand::ShootCommand(Player* player, Cell* cell)
    : CellCommand(player, cell) {}

void ShootCommand::Execute(bool is_remote) {
  if ((!is_remote && m_loop->Blocked()) || !IsValid()) {
    return;
  }
  if (!is_remote) {
    Send();
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

<<<<<<< HEAD
bool ShootCommand::IsValid() const { return true; }
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
bool ShootCommand::IsValid() const { return !m_loop->Blocked(); }
=======
bool ShootCommand::IsValid() const { return !loop_->Blocked(); }
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)

void ShootCommand::Send() {
<<<<<<< HEAD
  size_t index =
      m_cell->GetCoord().x * m_loop->GetSize().y + m_cell->GetCoord().y;
  m_loop->GetNetwork().Send("shoot", std::to_string(index));
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
  size_t index = m_cell->GetCoord().x * m_loop->GetSize().y + m_cell->GetCoord().y;
  m_loop->GetNetwork().Send("shoot", std::to_string(index));
=======
  size_t index = cell_->GetCoord().x * loop_->GetSize().y + cell_->GetCoord().y;
  loop_->GetNetwork().Send("shoot", std::to_string(index));
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)
}

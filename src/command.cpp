#include "../lib/command.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/game.hpp"
#include "../lib/player.hpp"
#include "../lib/window.hpp"

GameLoop* Command::m_loop = nullptr;

Command::Command() : m_type(Event::Count) {}

Command::Command(const Event::EventType& type) : m_type(type) {}

const Event::EventType& Command::GetType() { return m_type; }

<<<<<<< HEAD
SetCommand::SetCommand(const string& str) : str_(str) {}
||||||| 58d15e7
SetButtonsCommand::SetButtonsCommand(const string& str) : str_(str) {}
=======
void IPBoxCommand::Execute(bool is_remote) {
  m_loop->GetWnd().SetShow("client", "status", false);
>>>>>>> dev-ntheme

<<<<<<< HEAD
void SetCommand::Execute() {
  if (str_ == "menu") {
    loop_->Clear();
||||||| 58d15e7
bool SetButtonsCommand::Execute() {
  if(str_ == "menu") {
    loop_->Clear();
=======
  size_t code = m_loop->GetWnd().GetEvent().text.unicode;

  if (code == 8 && !m_loop->GetWnd().GetBoxes()["ip"].empty()) {
    m_loop->GetWnd().GetBoxes()["ip"].pop_back();
  } else if (code == 13) {
    IPClientCommand().Execute();
  } else if (code >= 46 && code <= 58 && code != 47 &&
             m_loop->GetWnd().GetBoxes()["ip"].size() < 21) {
    m_loop->GetWnd().GetBoxes()["ip"].push_back(static_cast<char>(code));
>>>>>>> dev-ntheme
  }
<<<<<<< HEAD
  loop_->GetWnd().SetButtons(str_);
||||||| 58d15e7
  loop_->GetWindow()->SetButtons(str_);
  return true;
=======
  m_loop->GetWnd().SetObject("client", "box", 1,
                             m_loop->GetWnd().GetBoxes()["ip"]);
>>>>>>> dev-ntheme
}

<<<<<<< HEAD
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

void PortBoxCommand::Execute() {
  loop_->GetWnd().SetShow("settings", "status", 1, false);

  size_t code = loop_->GetWnd().GetEvent().text.unicode;

  if (code == 8 && !loop_->GetWnd().GetBox().empty()) {
    loop_->GetWnd().GetBox().pop_back();
  } else if (code == 13) {
    SavePortCommand().Execute();
  } else if (code >= 48 && code <= 58 && loop_->GetWnd().GetBox().size() < 5) {
    loop_->GetWnd().GetBox().push_back(static_cast<char>(code));
  }
  loop_->GetWnd().SetObject("settings", "box", 1, loop_->GetWnd().GetBox());
}

std::string SaveIPCommand::ip_num_r =
    R"(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]))";
std::string SaveIPCommand::ip_port_r =
    R"(([0-9]|[1-9][0-9]{1,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5]))";
std::string SaveIPCommand::ip_str_r =
    R"(^()" + ip_num_r + R"(\.){3})" + ip_num_r + R"(:)" + ip_port_r;
std::regex SaveIPCommand::ip_regex(SaveIPCommand::ip_str_r);
std::regex SavePortCommand::port_regex(
    R"(([0-9]|[1-9][0-9]{1,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5]))");

void ServerCommand::Execute() {
  loop_->GetWnd().SetButtons("waiting");
  loop_->GetNetwork().ServerConnect();
}

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

void SavePortCommand::Execute() {
  loop_->GetWnd().SetShow("settings", "status", 1, false);
  loop_->GetWnd().SetShow("settings", "status", 2, false);
  
  string text = loop_->GetWnd().GetBox();
  if (!std::regex_match(text, port_regex)) {
    loop_->GetWnd().SetShow("settings", "status", 1, true);
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

void TerminateCommand::Execute() {
  loop_->GetNetwork().Terminate();
  loop_->Terminate();
  loop_->GetWnd().SetButtons("play");
}

ExecCommand::ExecCommand(GameWindow& obj, const Event::EventType& type,
                         void (*func)(GameWindow& obj))
    : Command(type), obj_(obj), func_(func) {}
||||||| 58d15e7
template <typename Type>
ExecCommand<Type>::ExecCommand(Type* obj, const Event::EventType& type,
                               void (*func)(Type* obj))
    : Command(type), obj_(obj), func_(func) {}
=======
void PortBoxCommand::Execute(bool is_remote) {
  m_loop->GetWnd().SetShow("settings", "port_status", false, 1);
>>>>>>> dev-ntheme

<<<<<<< HEAD
void ExecCommand::Execute() { (*func_)(obj_); }
||||||| 58d15e7
template <typename Type>
bool ExecCommand<Type>::Execute() {
  (*func_)(obj_);
  return true;
}
=======
  size_t code = m_loop->GetWnd().GetEvent().text.unicode;

  if (code == 8 && !m_loop->GetWnd().GetBoxes()["port"].empty()) {
    m_loop->GetWnd().GetBoxes()["port"].pop_back();
  } else if (code == 13) {
    PortCommand().Execute();
  } else if (code >= 48 && code <= 58 &&
             m_loop->GetWnd().GetBoxes()["port"].size() < 5) {
    m_loop->GetWnd().GetBoxes()["port"].push_back(static_cast<char>(code));
  }
  m_loop->GetWnd().SetObject("settings", "port_box", 1,
                             m_loop->GetWnd().GetBoxes()["port"]);
}
>>>>>>> dev-ntheme

std::string IPClientCommand::m_ip_addr =
    R"(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]))";
std::string IPClientCommand::m_ip_port =
    R"(([0-9]|[1-9][0-9]{1,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5]))";
std::string IPClientCommand::m_ip_full =
    R"(^()" + m_ip_addr + R"(\.){3})" + m_ip_addr + R"(:)" + m_ip_port;
std::regex IPClientCommand::m_ip_regex(IPClientCommand::m_ip_full);
std::regex PortCommand::m_port_regex(IPClientCommand::m_ip_port);

void IPClientCommand::Execute(bool is_remote) {
  m_loop->GetWnd().SetShow("client", "status", false);

<<<<<<< HEAD
void AddCellCommand::Execute() {
  Send();
  string scene = "select_" + std::to_string(player_->GetIndex());
  loop_->GetWnd().SetShow(scene, "status", 0, false);
  loop_->GetWnd().SetShow(scene, "status", 2, false);

  if (!IsValid()) {
    loop_->GetWnd().SetShow(scene, "status", 1, true);
    return;
||||||| 58d15e7
bool AddCellCommand::Execute() {
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
=======
  auto ip_got = ParseIp();
  if (ip_got.first.empty()) {
    m_loop->GetWnd().SetShow("client", "status", true, 1);
    return;
  }
  if (m_loop->GetNetwork().GetPort() == ip_got.second) {
    m_loop->GetWnd().SetShow("client", "status", true, 4);
    return;
  }
  m_loop->GetNetwork().ClientConnect(ip_got);
}

pair<string, size_t> IPClientCommand::ParseIp() {
  string text = m_loop->GetWnd().GetBoxes()["ip"];
  if (!std::regex_match(text, m_ip_regex)) {
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

void IPServerCommand::Execute(bool is_remote) {
  SetSceneCommand("server").Execute();
  m_loop->GetNetwork().ServerConnect();
}

void PortCommand::Execute(bool is_remote) {
  if (m_loop->GetNetwork().Connected()) {
    return;
  }
  m_loop->GetWnd().SetShow("settings", "port_status", false);

  string text = m_loop->GetWnd().GetBoxes()["port"];
  if (!std::regex_match(text, m_port_regex)) {
    m_loop->GetWnd().SetShow("settings", "port_status", true, 1);
    return;
  }

  size_t port_backup = m_loop->GetNetwork().GetPort();
  switch (m_loop->GetNetwork().UpdatePort(std::stoi(text))) {
    case Socket::Done:
      m_loop->GetWnd().SetShow("settings", "port_status", true, 0);
      sf::sleep(sf::milliseconds(kMoveSleep));
      m_loop->GetWnd().SetShow("settings", "port_status", false, 0);
      break;
    default:
      m_loop->GetNetwork().UpdatePort(port_backup);
      m_loop->GetWnd().SetShow("settings", "port_status", true, 2);
  }
}

VolumeCommand::VolumeCommand(CMDVolume type) : m_type(type) {}

void VolumeCommand::Execute(bool is_remote) {
  m_loop->GetWnd().SetVolume(m_type);
}

SetSceneCommand::SetSceneCommand(const string& m_str)
    : Command(Event::Closed), m_str(m_str) {}

deque<string> SetSceneCommand::m_stack = {"menu"};

void DisconnectCommand::Execute(bool is_remote) {
  m_loop->Clear();
  m_loop->GetNetwork().Disconnect(is_remote);
  if (m_loop->GetWnd().GetMusic("game").getStatus() == SoundSource::Playing) {
    m_loop->GetWnd().GetMusic("game").stop();
    m_loop->GetWnd().GetMusic("main").play();
  }
}

void SetSceneCommand::Execute(bool is_remote) {
  if (m_str == "ficha") {
    m_loop->GetWnd().Ficha();
    return;
  }
  if (m_str == "adios" || (m_str == "back" && m_stack.back() == "menu")) {
    DisconnectCommand().Execute(true);
    m_loop->GetWnd().close();
    return;
  }

  if (m_str == "back") {
    auto size = m_stack.back().size();
    if (m_str == "back" &&
        (m_stack.back() == "won_0" || m_stack.back() == "won_1")) {
      m_stack.resize(2);
      DisconnectCommand().Execute(true);
    } else if (m_stack.back() == "server" || m_stack.back() == "client" ||
               m_stack.back() == "waiting" ||
               m_stack.back().substr(0, size - 1) == "select_" ||
               m_stack.back().substr(0, size - 1) == "play_") {
      DisconnectCommand().Execute(true);
    }
    m_stack.pop_back();
  } else {
    m_stack.push_back(m_str);
    if (m_str == "settings") {
      if (m_loop->GetNetwork().Connected()) {
        m_loop->GetWnd().SetShow(m_str, "port_save", false);
      } else {
        m_loop->GetWnd().SetShow(m_str, "port_save", true);
      }
      m_loop->GetWnd().GetBoxes()["port"] =
          bs::atos(m_loop->GetNetwork().GetPort());
      m_loop->GetWnd().SetObject(m_str, "port_box", 1,
                                 m_loop->GetWnd().GetBoxes()["port"]);
    }
  }
  m_loop->GetWnd().SetButtons(m_stack.back());
}
CellCommand::CellCommand(Player* play, Cell* cell)
    : m_player(play), m_cell(cell) {}

AddCellCommand::AddCellCommand(Player* play, Cell* cell)
    : CellCommand(play, cell) {}

void AddCellCommand::Execute(bool is_remote) {
  string scene = "select_" + bs::atos(m_player->GetIndex());
  m_loop->GetWnd().SetShow(scene, "status", false);
  if (!IsValid()) {
    m_loop->GetWnd().SetShow(scene, "status", true, 1);
    return;
  }

  switch (m_cell->GetState()) {
    case CellState::Clear:
      m_player->m_ship_in_process.AddCell(m_cell);
      break;
    default:
      m_player->m_ship_in_process.EraseCell(m_cell);
  }
  m_loop->GetWnd().DrawObjects();
  if (!is_remote) {
    Send();
>>>>>>> dev-ntheme
  }
<<<<<<< HEAD
  if (cell_->GetState() == State::Clear) {
    player_->ship_in_process_.AddCell(cell_);
  } else {
    player_->ship_in_process_.EraseCell(cell_);
  }
  loop_->GetWnd().SetShow(scene, "status", 1, false);
||||||| 58d15e7
  loop_->GetWindow()->DrawObjects();
  return valid;
=======
>>>>>>> dev-ntheme
}

bool AddCellCommand::IsValid() const {
<<<<<<< HEAD
  if (loop_->Blocked()) {
    return false;
  }
  return cell_->GetState() == State::Clear ||
         cell_->GetState() == State::Chosen;
||||||| 58d15e7
  return cell_->GetState() == State::Clear ||
         cell_->GetState() == State::Chosen;
=======
  return m_cell->GetState() == CellState::Clear ||
         m_cell->GetState() == CellState::Chosen;
>>>>>>> dev-ntheme
}

<<<<<<< HEAD
void AddCellCommand::Send() {
  size_t index = cell_->GetCoord().x * loop_->GetSize().y + cell_->GetCoord().y;
  loop_->GetNetwork().Send("add_cell", std::to_string(index));
}

AddShipCommand::AddShipCommand(Player* player) : player_(player) {}
||||||| 58d15e7
AddShipCommand::AddShipCommand(Player* player) : player_(player) {}
=======
void AddCellCommand::Send() {
  size_t ind = m_cell->GetCoord().x * m_loop->kSize.y + m_cell->GetCoord().y;
  m_loop->GetNetwork().Send("add_cell", bs::atos(ind));
}
>>>>>>> dev-ntheme

<<<<<<< HEAD
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
||||||| 58d15e7
bool AddShipCommand::Execute() {
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
=======
AddShipCommand::AddShipCommand(Player* play) : m_player(play) {}

void AddShipCommand::Execute(bool is_remote) {
  string scene = "select_" + bs::atos(m_player->GetIndex());
  m_loop->GetWnd().SetShow(scene, "status", false);
  if (!IsValid()) {
    m_loop->GetWnd().SetShow(scene, "status", true, 2);
    return;
  }

  m_player->AddShip();
  if (!is_remote) {
    Send();
  }

  m_loop->GetWnd().SetShow(scene, "status", true, 0);
  sf::sleep(sf::milliseconds(kMoveSleep));
  m_loop->GetWnd().SetShow(scene, "status", false, 0);

  if (m_player->GetShipCount() == m_loop->kShips) {
    auto play = m_loop->GetLocalPlayer();
    m_player->GetMField()->RemoveProhibited();
    m_loop->GetWnd().SetShow("play_" + bs::atos(m_player->GetIndex()), "turn",
                             true, m_player->GetIndex() ^ 1);

    if (m_player->GetRival()->GetShipCount() == m_loop->kShips) {
      m_loop->GetWnd().GetMusic("main").pause();
      m_loop->GetWnd().GetMusic("game").play();
      SetSceneCommand("play_" + bs::atos(play)).Execute();
    } else if (m_player->GetIndex() == m_loop->GetLocalPlayer()) {
      SetSceneCommand("waiting").Execute();
    }
    m_loop->GetWnd().DrawObjects();
>>>>>>> dev-ntheme
  }
}

bool AddShipCommand::IsValid() const {
<<<<<<< HEAD
  if (loop_->Blocked() || !player_->GetShipInProcess()->IsClassic()) {
||||||| 58d15e7
  if (!player_->GetShipInProcess()->IsClassic()) {
=======
  if (!m_player->GetShipInProcess()->IsClassic()) {
>>>>>>> dev-ntheme
    return false;
  }
<<<<<<< HEAD
  return player_->GetNumberOfShips(player_->GetShipInProcess()->GetSize()) <
         5 - player_->GetShipInProcess()->GetSize();
||||||| 58d15e7
  if (player_->GetNumberOfShipsSized(player_->GetShipInProcess()->GetSize()) >=
      5 - player_->GetShipInProcess()->GetSize()) {
    return false;
  }
  return true;
=======
  return m_player->GetNumShips(m_player->GetShipInProcess()->GetSize()) <
         5 - m_player->GetShipInProcess()->GetSize();
>>>>>>> dev-ntheme
}

<<<<<<< HEAD
void AddShipCommand::Send() { loop_->GetNetwork().Send("add_ship"); }

ShootCommand::ShootCommand(Player* player, Cell* cell)
    : CellCommand(player, cell) {}
||||||| 58d15e7
ShootCommand::ShootCommand(Player* player, Cell* cell)
    : CellCommand(player, cell) {}
=======
void AddShipCommand::Send() { m_loop->GetNetwork().Send("add_ship"); }
>>>>>>> dev-ntheme

<<<<<<< HEAD
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
||||||| 58d15e7
bool ShootCommand::Execute() {
  bool valid = IsValid();
  if (valid) {
    ShotResult shot_result;
    player_->Shoot(cell_, shot_result);
    if (player_->GetRival()->GetShipCount() == 0) {
      loop_->GetWindow()->SetButtons("won_" +
                                     std::to_string(player_->GetIndex()));
    }
    if (player_->GetLastShotResult() == ShotResult::Miss) {
      loop_->GetWindow()->SetButtons("turn_" +
                                     std::to_string(1 - player_->GetIndex()));
      sf::sleep(sf::milliseconds(2000));
      loop_->GetWindow()->SetButtons("play_" +
                                     std::to_string(1 - player_->GetIndex()));
    }
=======
ShootCommand::ShootCommand(Player* play, Cell* cell)
    : CellCommand(play, cell) {}

void ShootCommand::Execute(bool is_remote) {
  if (!IsValid() ^ is_remote) {
    return;
  }
  if (!is_remote) {
    Send();
  }

  size_t play = m_loop->GetLocalPlayer();
  ShotState shot_result = m_player->Shoot(m_cell);
  SetSceneCommand("play_" + bs::atos(play)).Execute();
  if (m_player->GetRival()->GetShipCount() == 0) {
    SetSceneCommand("won_" + bs::atos(m_player->GetIndex() ^ play)).Execute();
    m_loop->GetBlocked() = false;
  }
  if (shot_result == ShotState::Miss) {
    size_t ind = play == m_player->GetIndex() ? 1 : 0;
    m_loop->GetBlocked() = !m_loop->GetBlocked();
    m_loop->GetWnd().SetShow("play_" + bs::atos(play), "turn", false, ind ^ 1);
    m_loop->GetWnd().SetShow("play_" + bs::atos(play), "turn", true, ind);
>>>>>>> dev-ntheme
  }
}

<<<<<<< HEAD
bool ShootCommand::IsValid() const { return !loop_->Blocked(); }

void ShootCommand::Send() {
  size_t index = cell_->GetCoord().x * loop_->GetSize().y + cell_->GetCoord().y;
  loop_->GetNetwork().Send("shoot", std::to_string(index));
}
||||||| 58d15e7
bool ShootCommand::IsValid() const { return true; }
=======
bool ShootCommand::IsValid() const { return m_loop->GetBlocked(); }

void ShootCommand::Send() {
  size_t ind = m_cell->GetCoord().x * m_loop->kSize.y + m_cell->GetCoord().y;
  m_loop->GetNetwork().Send("shoot", bs::atos(ind));
}
>>>>>>> dev-ntheme

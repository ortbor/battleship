#include "../lib/command.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/game.hpp"
#include "../lib/player.hpp"
#include "../lib/window.hpp"

GameLoop* Command::m_loop = nullptr;

Command::Command() : m_type(Event::Closed) {}

Command::Command(const Event::EventType& type) : m_type(type) {}

const Event::EventType& Command::GetType() { return m_type; }

void IPBoxCommand::Execute(bool is_remote) {
  m_loop->GetWnd().SetShow("client", "status", 1, false);
  m_loop->GetWnd().SetShow("client", "status", 2, false);
  m_loop->GetWnd().SetShow("client", "status", 3, false);

  size_t code = m_loop->GetWnd().GetEvent().text.unicode;

  if (code == 8 && !m_loop->GetWnd().GetBoxes()["ip"].empty()) {
    m_loop->GetWnd().GetBoxes()["ip"].pop_back();
  } else if (code == 13) {
    IPClientCommand().Execute();
  } else if (code >= 46 && code <= 58 && code != 47 &&
             m_loop->GetWnd().GetBoxes()["ip"].size() < 21) {
    m_loop->GetWnd().GetBoxes()["ip"].push_back(static_cast<char>(code));
  }
  m_loop->GetWnd().SetObject("client", "box", 1,
                             m_loop->GetWnd().GetBoxes()["ip"]);
}

void PortBoxCommand::Execute(bool is_remote) {
  m_loop->GetWnd().SetShow("settings", "port_status", 1, false);

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

std::string IPClientCommand::m_ip_addr =
    R"(([0-9]|[1-9][0-9]|1[0-9]{2}|2[0-4][0-9]|25[0-5]))";
std::string IPClientCommand::m_ip_port =
    R"(([0-9]|[1-9][0-9]{1,3}|[1-5][0-9]{4}|6[0-4][0-9]{3}|65[0-4][0-9]{2}|655[0-2][0-9]|6553[0-5]))";
std::string IPClientCommand::m_ip_full =
    R"(^()" + m_ip_addr + R"(\.){3})" + m_ip_addr + R"(:)" + m_ip_port;
std::regex IPClientCommand::m_ip_regex(IPClientCommand::m_ip_port);
std::regex PortCommand::m_port_regex(IPClientCommand::m_ip_port);

void IPClientCommand::Execute(bool is_remote) {
  m_loop->Blocked() = false;
  m_loop->SetLocalPlayer(0);
  m_loop->GetWnd().SetShow("client", "status", 2, false);
  m_loop->GetWnd().SetShow("client", "status", 3, false);

  auto ip_got = ParseIp();
  if (ip_got.first.empty()) {
    m_loop->GetWnd().SetShow("client", "status", 1, true);
    return;
  }

  switch (m_loop->GetNetwork().ClientConnect(ip_got)) {
    case Socket::Done:
      m_loop->GetWnd().SetShow("client", "status", 0, true);
      sf::sleep(sf::milliseconds(kMoveSleep));
      m_loop->LaunchNetwork();
      m_loop->GetWnd().SetButtons("select_0");
      break;
    case Socket::Disconnected:
      m_loop->GetWnd().SetShow("client", "status", 2, true);
      break;
    default:
      m_loop->GetWnd().SetShow("client", "status", 3, true);
  }
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
    return;
  }

  size_t port_backup = m_loop->GetNetwork().GetPort();
  switch (m_loop->GetNetwork().UpdatePort(std::stoi(text))) {
    case Socket::Done:
      m_loop->GetWnd().SetShow("settings", "port_status", 0, true);
      sf::sleep(sf::milliseconds(kMoveSleep));
      m_loop->GetWnd().SetShow("settings", "port_status", 0, false);
      break;
    default:
      m_loop->GetNetwork().UpdatePort(port_backup);
      m_loop->GetWnd().SetShow("settings", "port_status", 2, true);
  }
}

void TerminateCommand::Execute(bool is_remote) {
  m_loop->GetNetwork().Terminate();
  m_loop->Terminate();
  m_loop->GetWnd().SetButtons("play");
}

WindowCommand::WindowCommand(CMDType request) : m_request(request) {}

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

CellCommand::CellCommand(Player* player, Cell* cell)
    : m_player(player), m_cell(cell) {}

AddCellCommand::AddCellCommand(Player* player, Cell* cell)
    : CellCommand(player, cell) {}

void AddCellCommand::Execute(bool is_remote) {
  string scene = "select_" + std::to_string(m_player->GetIndex());
  m_loop->GetWnd().SetShow(scene, "status", 0, false);
  m_loop->GetWnd().SetShow(scene, "status", 2, false);
  std::cout << "executing\n";
  std::cout.flush();
  if ((!is_remote && m_loop->Blocked()) || !IsValid()) {
    m_loop->GetWnd().SetShow(scene, "status", 1, true);
    return;
  }
  if (!is_remote) {
    Send();
  }

  std::cout << "executing3\n";
  std::cout.flush();
  if (m_cell->GetState() == CellState::Clear) {
    m_player->m_ship_in_process.AddCell(m_cell);
  } else {
    m_player->m_ship_in_process.EraseCell(m_cell);
  }
  m_loop->GetWnd().SetShow(scene, "status", 1, false);
  std::cout << "executing4\n";
  std::cout.flush();
}

bool AddCellCommand::IsValid() const {
  return m_cell->GetState() == CellState::Clear ||
         m_cell->GetState() == CellState::Chosen;
}

void AddCellCommand::Send() {
  size_t index =
      m_cell->GetCoord().x * m_loop->GetSize().y + m_cell->GetCoord().y;
  m_loop->GetNetwork().Send("add_cell", std::to_string(index));
}

AddShipCommand::AddShipCommand(Player* player) : m_player(player) {}

void AddShipCommand::Execute(bool is_remote) {
  string scene = "select_" + std::to_string(m_player->GetIndex());
  m_loop->GetWnd().SetShow(scene, "status", 1, false);
  if ((!is_remote && m_loop->Blocked()) || !IsValid()) {
    std::cout << "blocked(\n";
    std::cout.flush();
    m_loop->GetWnd().SetShow(scene, "status", 0, false);
    m_loop->GetWnd().SetShow(scene, "status", 2, true);
    return;
  }
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
    } else {
      m_loop->GetWnd().GetMusic("main").stop();
      m_loop->GetWnd().GetMusic("game").play();
      m_loop->GetWnd().SetButtons("play_0");
    }
  }
}

bool AddShipCommand::IsValid() const {
  if (!m_player->GetShipInProcess()->IsClassic()) {
    return false;
  }
  return m_player->GetNumberOfShips(m_player->GetShipInProcess()->GetSize()) <
         5 - m_player->GetShipInProcess()->GetSize();
}

void AddShipCommand::Send() { m_loop->GetNetwork().Send("add_ship"); }

ShootCommand::ShootCommand(Player* player, Cell* cell)
    : CellCommand(player, cell) {}

void ShootCommand::Execute(bool is_remote) {
  if ((!is_remote && m_loop->Blocked()) || !IsValid()) {
    return;
  }
  if (!is_remote) {
    Send();
  }

  size_t index = m_player->GetIndex();
  ShotState shot_result;
  m_player->Shoot(m_cell, shot_result);
  if (m_player->GetRival()->GetShipCount() == 0) {
    m_loop->GetWnd().SetButtons("won_" + std::to_string(index));
    m_loop->Blocked() = false;
  }
  if (m_player->GetLastShotResult() == ShotState::Miss) {
    m_loop->GetWnd().SetButtons("turn_" + std::to_string(1 - index));
    sf::sleep(sf::milliseconds(2000));
    m_loop->GetWnd().SetButtons("play_" + std::to_string(1 - index));
    m_loop->Blocked() = !m_loop->Blocked();
  }
}

bool ShootCommand::IsValid() const { return true; }

void ShootCommand::Send() {
  size_t index =
      m_cell->GetCoord().x * m_loop->GetSize().y + m_cell->GetCoord().y;
  m_loop->GetNetwork().Send("shoot", std::to_string(index));
}

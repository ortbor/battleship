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

void IPBoxCommand::Execute(bool is_remote) {
  m_loop->GetWnd().SetShow("client", "status", 1, false);
  m_loop->GetWnd().SetShow("client", "status", 2, false);
  m_loop->GetWnd().SetShow("client", "status", 3, false);
  m_loop->GetWnd().SetShow("client", "status", 4, false);

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
std::regex IPClientCommand::m_ip_regex(IPClientCommand::m_ip_full);
std::regex PortCommand::m_port_regex(IPClientCommand::m_ip_port);

void IPClientCommand::Execute(bool is_remote) {
  m_loop->GetBlocked() = false;
  m_loop->SetLocalPlayer(0);
  m_loop->GetWnd().SetShow("client", "status", 2, false);
  m_loop->GetWnd().SetShow("client", "status", 3, false);
  m_loop->GetWnd().SetShow("client", "status", 4, false);

  auto ip_got = ParseIp();
  if (ip_got.first.empty()) {
    m_loop->GetWnd().SetShow("client", "status", 1, true);
    return;
  }

  if (m_loop->GetNetwork().GetPort() == ip_got.second) {
    m_loop->GetWnd().SetShow("client", "status", 4, true);
    return;
  }

  switch (m_loop->GetNetwork().ClientConnect(ip_got)) {
    case Socket::Done:
      m_loop->GetWnd().SetShow("client", "status", 0, true);
      sf::sleep(sf::milliseconds(kMoveSleep));
      m_loop->GetWnd().SetShow("client", "status", 0, false);
      m_loop->LaunchNetwork();
      m_loop->GetNetwork().GetConnected() = true;
      m_loop->GetWnd().GetBoxes()["ip"].clear();
      m_loop->GetWnd().SetButtons("select_" +
                                  bs::atos(m_loop->GetLocalPlayer()));
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
  m_loop->GetBlocked() = true;
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

void DisconnectCommand::Execute(bool is_remote) {
  std::cout << "aaa";
  std::cout.flush();
  m_loop->GetNetwork().Disconnect();
  m_loop->GetWnd().SetButtons("play");
}

void RestartCommand::Execute(bool is_remote) {
  DisconnectCommand().Execute();
  m_loop->Clear();
  if (m_loop->GetWnd().GetMusic("game").getStatus() == SoundSource::Playing) {
    m_loop->GetWnd().GetMusic("game").stop();
    m_loop->GetWnd().GetMusic("main").play();
  }
}

WindowCommand::WindowCommand(CMDType request)
    : Command(Event::Closed), m_request(request) {}

void WindowCommand::Execute(bool is_remote) {
  switch (m_request) {
    case CMDType::Close:
      RestartCommand().Execute();
      m_loop->GetWnd().close();
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

SetSceneCommand::SetSceneCommand(const string& str) : str_(str) {}

void SetSceneCommand::Execute(bool is_remote) {
  if (str_ == "menu") {
    m_loop->Clear();
  } else if (str_ == "settings") {
    m_loop->GetWnd().GetBoxes()["ip"] =
        bs::atos(m_loop->GetNetwork().GetPort());
    m_loop->GetWnd().SetObject("settings", "port_box", 1,
                               m_loop->GetWnd().GetBoxes()["ip"]);
  }
  m_loop->GetWnd().SetButtons(str_);
}
CellCommand::CellCommand(Player* play, Cell* cell)
    : m_player(play), m_cell(cell) {}

AddCellCommand::AddCellCommand(Player* play, Cell* cell)
    : CellCommand(play, cell) {}

void AddCellCommand::Execute(bool is_remote) {
  string scene = "select_" + bs::atos(m_player->GetIndex());
  m_loop->GetWnd().SetShow(scene, "status", 1, false);
  m_loop->GetWnd().SetShow(scene, "status", 2, false);
  if (!IsValid()) {
    m_loop->GetWnd().SetShow(scene, "status", 1, true);
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
  }
}

bool AddCellCommand::IsValid() const {
  return m_cell->GetState() == CellState::Clear ||
         m_cell->GetState() == CellState::Chosen;
}

void AddCellCommand::Send() {
  size_t ind = m_cell->GetCoord().x * m_loop->kSize.y + m_cell->GetCoord().y;
  m_loop->GetNetwork().Send("add_cell", bs::atos(ind));
}

AddShipCommand::AddShipCommand(Player* play) : m_player(play) {}

void AddShipCommand::Execute(bool is_remote) {
  string scene = "select_" + bs::atos(m_player->GetIndex());
  m_loop->GetWnd().SetShow(scene, "status", 1, false);
  m_loop->GetWnd().SetShow(scene, "status", 2, false);
  if (!IsValid()) {
    m_loop->GetWnd().SetShow(scene, "status", 2, true);
    return;
  }

  m_player->AddShip();
  if (!is_remote) {
    Send();
  }

  m_loop->GetWnd().SetShow(scene, "status", 0, true);
  sf::sleep(sf::milliseconds(kMoveSleep));
  m_loop->GetWnd().SetShow(scene, "status", 0, false);

  if (m_player->GetShipCount() == m_loop->kShips) {
    auto play = m_loop->GetLocalPlayer();
    m_player->GetMField()->RemoveProhibited();
    m_loop->GetWnd().SetShow("play_" + bs::atos(m_player->GetIndex()), "turn",
                             m_player->GetIndex() ^ 1, true);

    if (m_player->GetRival()->GetShipCount() == m_loop->kShips) {
      m_loop->GetWnd().GetMusic("main").pause();
      m_loop->GetWnd().GetMusic("game").play();
      m_loop->GetWnd().SetButtons("play_" + bs::atos(play));
    } else if (m_player->GetIndex() == m_loop->GetLocalPlayer()) {
      m_loop->GetWnd().SetButtons("waiting");
    }
    m_loop->GetWnd().DrawObjects();
  }
}

bool AddShipCommand::IsValid() const {
  if (!m_player->GetShipInProcess()->IsClassic()) {
    return false;
  }
  return m_player->GetNumShips(m_player->GetShipInProcess()->GetSize()) <
         5 - m_player->GetShipInProcess()->GetSize();
}

void AddShipCommand::Send() { m_loop->GetNetwork().Send("add_ship"); }

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
  m_loop->GetWnd().SetButtons("play_" + bs::atos(play));
  if (m_player->GetRival()->GetShipCount() == 0) {
    m_loop->GetWnd().SetButtons("won_" + bs::atos(m_player->GetIndex() ^ play));
    m_loop->GetBlocked() = false;
  }
  if (shot_result == ShotState::Miss) {
    size_t ind = play == m_player->GetIndex() ? 1 : 0;
    m_loop->GetBlocked() = !m_loop->GetBlocked();
    m_loop->GetWnd().SetShow("play_" + bs::atos(play), "turn", ind ^ 1, false);
    m_loop->GetWnd().SetShow("play_" + bs::atos(play), "turn", ind, true);
  }
}

bool ShootCommand::IsValid() const { return m_loop->GetBlocked(); }

void ShootCommand::Send() {
  size_t ind = m_cell->GetCoord().x * m_loop->kSize.y + m_cell->GetCoord().y;
  m_loop->GetNetwork().Send("shoot", bs::atos(ind));
}

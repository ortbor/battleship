#include "../lib/network.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/command.hpp"
#include "../lib/game.hpp"
#include "../lib/object.hpp"
#include "../lib/player.hpp"

Network::Network(GameLoop* loop)
    : m_connect_thr(&Network::ServerAccept, this), m_loop(loop) {
  m_listener.listen(2000);
}

size_t Network::GetPort() { return m_listener.getLocalPort(); }

Socket::Status Network::UpdatePort(size_t port) {
  return m_listener.listen(port);
}

void Network::Terminate() { m_connect_thr.terminate(); }

Socket::Status Network::ClientConnect(pair<IpAddress, size_t> address) {
  return m_socket.connect(address.first, address.second, sf::milliseconds(1500));
}

void Network::ServerAccept() {
  m_listener.accept(m_socket);
  m_loop->LaunchNetwork();
  m_loop->Blocked() = true;
  m_loop->GetWnd().SetButtons("select_0");
}

void Network::ServerConnect() { m_connect_thr.launch(); }

void Network::Send(std::string command_type, std::string coords) {
  m_packet.clear();
  m_packet << command_type << coords;
  if (m_socket.send(m_packet) == Socket::Done) {
    std::cout << "sent\n";
    std::cout.flush();
  }
}

Command* Network::GetCommand() {
  m_socket.receive(m_packet);
  std::string command_type;
  m_packet >> command_type;

  auto& buttons = m_loop->GetWnd().GetButtons();
  if (command_type == "add_ship") {
    return buttons.Get("select_1", "ship")->GetCommand().get();
  }

  std::string coords;
  m_packet >> coords;
  if (command_type == "add_cell") {
    return buttons.Get("select_1", "cell_m_" + coords)->GetCommand().get();
  }
  return buttons.Get("play_1", "cell_r_" + coords)->GetCommand().get();
}

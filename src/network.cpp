#include "../lib/network.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/command.hpp"
#include "../lib/game.hpp"
#include "../lib/object.hpp"
#include "../lib/player.hpp"

Network::Network(GameLoop* loop)
    : m_connect_thr(&Network::ServerAccept, this), m_loop(loop) {
  m_listener.listen(2001);
}

size_t Network::GetPort() { return m_listener.getLocalPort(); }

Socket::Status Network::UpdatePort(size_t port) {
  return m_listener.listen(port);
}

void Network::Terminate() { m_connect_thr.terminate(); }

void Network::ServerAccept() {
  m_listener.accept(m_socket);
  m_loop->LaunchNetwork();
  m_loop->Blocked() = true;
  m_loop->GetWnd().SetButtons("select_" +
                              std::to_string(m_loop->GetLocalPlayer()));
}

void Network::ServerConnect() { m_connect_thr.launch(); }

Socket::Status Network::ClientConnect(pair<IpAddress, size_t> address) {
  return m_socket.connect(address.first, address.second,
                          sf::milliseconds(1500));
}

void Network::Send(std::string command_type, std::string coords) {
  m_packet_out.clear();
  m_packet_out << command_type << coords;
  m_socket.send(m_packet_out);
}

Command* Network::GetCommand() {
  m_packet_in.clear();
  m_socket.receive(m_packet_in);
  std::string command_type;
  m_packet_in >> command_type;
  std::string coords;
  m_packet_in >> coords;

  auto ind = std::to_string(1 - m_loop->GetLocalPlayer());
  auto& buttons = m_loop->GetWnd().GetButtons();
  if (command_type == "add_ship") {
    return buttons.Get("select_" + ind, "ship")->GetCommand().get();
  }

  if (command_type == "add_cell") {
    return buttons.Get("select_" + ind, "cell_m_" + coords)->GetCommand().get();
  }
  return buttons.Get("play_" + ind, "cell_r_" + coords)->GetCommand().get();
}

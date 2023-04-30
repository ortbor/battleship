#include "../lib/network.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/command.hpp"
#include "../lib/game.hpp"
#include "../lib/object.hpp"
#include "../lib/player.hpp"

Network::Network(GameLoop* loop) : opened_port_(2001), loop_(loop) {}

void Network::UpdatePort(size_t port) { opened_port_ = port; }

Socket::Status Network::ServerConnect() {
  listener_.listen(opened_port_);
  return listener_.accept(socket_);
}

Socket::Status Network::ClientConnect(IpAddress m_ip, size_t port) {
  return socket_.connect(m_ip, port, sf::milliseconds(2000));
}

void Network::Send(std::string command_type, std::string coords) {
  packet_.clear();
  packet_ << command_type << coords;
  if (socket_.send(packet_) == Socket::Done) {
    std::cout << "sent\n";
    std::cout.flush();
  }
}

Command* Network::GetCommand() {
  while (socket_.getRemoteAddress() == IpAddress::None) {
  }
  if (socket_.receive(packet_) == Socket::Status::Done) {
    std::cout << "DEEEEESPACITO!";
    std::cout.flush();
  }
  std::string command_type;
  packet_ >> command_type;

  if (command_type == "add_ship") {
    return loop_->GetWnd().GetButtons()["select_1"]["ship"]->GetCommand().get();
  }
  std::string coords;
  packet_ >> coords;
  if (command_type == "add_cell") {
    std::cout << "adding\n";
    std::cout.flush();
    string cell = "cell" + coords;
    return loop_->GetWnd().GetButtons()["select_1"][cell]->GetCommand().get();
  }
  string cell = "cell_rival" + coords;
  return loop_->GetWnd().GetButtons()["play_1"][cell]->GetCommand().get();
}

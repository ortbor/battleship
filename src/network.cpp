#include "../lib/network.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/command.hpp"
#include "../lib/game.hpp"
#include "../lib/object.hpp"
#include "../lib/player.hpp"

Network::Network(GameLoop* loop) : opened_port_(2000), loop_(loop) {}

void Network::UpdatePort(size_t port) { opened_port_ = port; }

Socket::Status Network::ServerConnect() {
  listener_.listen(opened_port_);
  return listener_.accept(socket_);
  char buf[2000];
  size_t recei;
  socket_.receive(buf, sizeof(buf), recei);
  std::cout << buf << "DEEEEESPACITO!";
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
  if (socket_.receive(packet_) != Socket::Status::Done) {
    std::cout << "DEEEEESPACITO!";
    std::cout.flush();
  }
  std::string command_type;
  packet_ >> command_type;

  string choose = "select_" + std::to_string(1 - loop_->GetLocalPlayer());
  if (command_type == "add_ship") {
    return loop_->GetWindow().GetButtons()[choose]["ship"]->GetCommand().get();
  }
  std::string coords;
  packet_ >> coords;
  if (command_type == "add_cell") {
    std::cout << "adding\n";
    std::cout.flush();
    string cell = "cell" + coords;
    return loop_->GetWindow().GetButtons()[choose][cell]->GetCommand().get();
  }
  string player = "play_" + std::to_string(1 - loop_->GetLocalPlayer());
  string cell = "cell_rival" + coords;
  return loop_->GetWindow().GetButtons()[player][cell]->GetCommand().get();
}

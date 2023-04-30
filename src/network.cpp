#include "../lib/network.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/command.hpp"
#include "../lib/game.hpp"
#include "../lib/object.hpp"
#include "../lib/player.hpp"

Network::Network(GameLoop* loop)
    : connect_thr(&Network::ServerAccept, this), loop_(loop) {
  listener_.listen(2000);
}

Socket::Status Network::UpdatePort(size_t port) {
  return listener_.listen(port);
}

void Network::Terminate() { connect_thr.terminate(); }

void Network::ServerAccept() {
  listener_.accept(socket_);
  loop_->LaunckNetwork();
  loop_->Blocked() = true;
  loop_->GetWnd().SetButtons("select_0");
}

void Network::ServerConnect() { connect_thr.launch(); }

Socket::Status Network::ClientConnect(pair<IpAddress, size_t> address) {
  if (address.first.toString().size() == 0) {
    return Socket::Error;
  }
  return socket_.connect(address.first, address.second, sf::milliseconds(1500));
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
  socket_.receive(packet_);
  std::string command_type;
  packet_ >> command_type;

  auto& buttons = loop_->GetWnd().GetButtons();
  if (command_type == "add_ship") {
    return buttons["select_1"]["ship"]->GetCommand().get();
  }

  std::string coords;
  packet_ >> coords;
  if (command_type == "add_cell") {
    return buttons["select_1"]["cell" + coords]->GetCommand().get();
  }
  return buttons["play_1"]["cell_rival" + coords]->GetCommand().get();
}

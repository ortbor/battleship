#include "../lib/network.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/command.hpp"
#include "../lib/game.hpp"
#include "../lib/object.hpp"
#include "../lib/player.hpp"

Network::Network(GameLoop* loop)
    : connect_thr(&Network::ServerAccept, this), loop_(loop) {}

Socket::Status Network::UpdatePort(size_t port) {
  port_ = port;
  return listener_.listen(port);
}

void Network::Terminate() { connect_thr.terminate(); }

void Network::ServerAccept() {
  listener_.accept(in_socket_);
  listener_.accept(out_socket_);
  loop_->LaunckNetwork();
  loop_->Blocked() = true;
  loop_->GetWnd().SetButtons("select_0");
}

void Network::ServerConnect() {
  listener_.listen(port_);
  connect_thr.launch();
}

Socket::Status Network::ClientConnect(pair<IpAddress, size_t> address) {
  if (address.first.toString().empty()) {
    return Socket::Error;
  }
  in_socket_.connect(address.first, address.second, sf::milliseconds(1500));
  return out_socket_.connect(address.first, address.second, sf::milliseconds(1500));
}

void Network::Send(std::string command_type, std::string coords) {
  out_packet_.clear();
  out_packet_ << command_type << coords;
  if (out_socket_.send(out_packet_) == Socket::Done) {
    std::cout << "sent\n";
    std::cout.flush();
  }
}

Command* Network::GetCommand() {
  in_packet_.clear();
  in_socket_.receive(in_packet_);
  std::string command_type;
  in_packet_ >> command_type;
  std::cout << "got command " << command_type << "\n";
  std::string coords;
  in_packet_ >> coords;
  auto& buttons = loop_->GetWnd().GetButtons();
  if (command_type == "add_ship") {
    return buttons["select_" + std::to_string(1 - loop_->GetLocalPlayer())]["ship"]->GetCommand().get();
  }


  if (command_type == "add_cell") {
    return buttons["select_" + std::to_string(1 - loop_->GetLocalPlayer())]["cell" + coords]->GetCommand().get();
  }
  return buttons["play_" + std::to_string(1 - loop_->GetLocalPlayer())]["cell_rival" + coords]->GetCommand().get();
}

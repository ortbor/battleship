#include "../lib/network.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/command.hpp"
#include "../lib/game.hpp"
#include "../lib/object.hpp"
#include "../lib/player.hpp"

Network::Network(GameLoop* loop) : opened_port_(2000), loop_(loop) { }

Socket::Status Network::ClientConnect(IpAddress other_ip, size_t port) {
  listener_.listen(opened_port_);
  listener_.accept(server_socket_);

  other_ip_ = other_ip;
  port_ = port;
  if (server_socket_.connect("192.168.1.189", 2000, sf::milliseconds(1500)) == sf::Socket::Done) {
    std::cout << "done\n";
    std::cout.flush();
  }
  if (listener_.accept(server_socket_) == sf::Socket::Done) {
    std::cout << "done\n";
    std::cout.flush();
  }
  if (client_socket_.connect("192.168.1.189", 2000, sf::milliseconds(1500)) == sf::Socket::Done) {
    std::cout << "done\n";
    std::cout.flush();
  }
  //socket_.connect(other_ip, ip_port);
  return sf::Socket::Status::Done;
}

void Network::Send(std::string command_type, std::string coords) {
  packet_.clear();
  packet_ << command_type << coords;
  if (client_socket_.send(packet_) == sf::Socket::Done) {
    std::cout << "sent\n";
    std::cout.flush();
  }
}

Command* Network::GetCommand() {
  while (server_socket_.receive(packet_) != sf::Socket::Done) {}
  std::cout << "received\n";
  std::cout.flush();
  std::string command_type;
  packet_ >> command_type;
  if (command_type == "add_ship") {
    return loop_->GetWindow()
        .GetButtons()["select_" + std::to_string(1 - loop_->GetLocalPlayer())]
                     ["ship"]
        ->GetCommand()
        .get();
  }
  std::string coords;
  packet_ >> coords;
  if (command_type == "add_cell") {
    std::cout << "adding\n";
    std::cout.flush();
    return loop_->GetWindow()
        .GetButtons()["select_" + std::to_string(1 - loop_->GetLocalPlayer())]
                     ["cell" + coords]
        ->GetCommand()
        .get();
  }
  return loop_->GetWindow()
      .GetButtons()["play_" + std::to_string(1 - loop_->GetLocalPlayer())]
                   ["cell_rival" + coords]
      ->GetCommand()
      .get();
}
#include "../lib/network.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/command.hpp"
#include "../lib/game.hpp"
#include "../lib/object.hpp"
#include "../lib/player.hpp"


Network::Network(GameLoop* loop) : opened_port_(2000), loop_(loop) { }

void Network::SetMyIP(IpType type, size_t port) {
  switch (type)
  {
  case IpType::LOCAL:
    my_ip_.ip_address = IpAddress("127.0.0.1");
    break;
  case IpType::ROUTER:
    my_ip_.ip_address = IpAddress::getLocalAddress();
    break;
  case IpType::GLOBAL:
    my_ip_.ip_address = IpAddress::getPublicAddress();
  default:
    throw std::runtime_error("Unknown Network enum");
    break;
  }
  my_ip_.port = port;
}

Socket::Status Network::SetOtherIP(IpAddress m_ip, size_t port) {
  listener_.listen(opened_port_);
  listener_.accept(socket_);

  other_ip_ = other_ip;
  port_ = ip_port;
  if (server_socket_.connect("192.168.1.189", 2000, sf::milliseconds(1500)) == Socket::Done) {
    std::cout << "done\n";
    std::cout.flush();
  }
  if (listener_.accept(server_socket_) == Socket::Done) {
    std::cout << "done\n";
    std::cout.flush();
  }
  if (client_socket_.connect("192.168.1.189", 2000, sf::milliseconds(1500)) ==
      Socket::Done) {
    std::cout << "done\n";
    std::cout.flush();
  }
  return Socket::Status::Done;
}

void Network::Send(std::string command_type, std::string coords) {
  packet_.clear();
  packet_ << command_type << coords;
  if (client_socket_.send(packet_) == Socket::Done) {
    std::cout << "sent\n";
    std::cout.flush();
  }
}

Command* Network::GetCommand() {
  while (server_socket_.receive(packet_) != Socket::Done) {
  }
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
#pragma once

#include <SFML/Network.hpp>

#include "common.hpp"

class Network {
 public:
  explicit Network(GameLoop* loop);
  void SetOtherIP(sf::IpAddress other_ip, size_t ip_port);
  void Send(std::string command_type, std::string coords = "");
  Command* GetCommand();

 protected:
  size_t port_;
  sf::IpAddress other_ip_;
  sf::TcpSocket socket_;
  sf::TcpListener listener_;
  sf::Packet packet_;
  GameLoop* loop_;
};
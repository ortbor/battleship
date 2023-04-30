#pragma once

#include "common.hpp"

class Network {
 public:
  explicit Network(GameLoop* loop);
  void UpdatePort(size_t port);
  Socket::Status ServerConnect();
  Socket::Status ClientConnect(IpAddress m_ip, size_t port);
  void Send(std::string command_type, std::string coords = "");
  Command* GetCommand();

 protected:
  size_t port_;
  sf::IpAddress my_ip_;
  sf::IpAddress other_ip_;
  sf::TcpSocket socket_;
  sf::TcpListener listener_;
  sf::Packet packet_;
  size_t opened_port_;
  GameLoop* loop_;
};

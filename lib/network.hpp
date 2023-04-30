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
  size_t opened_port_;
  TcpSocket socket_;
  TcpListener listener_;
  Packet packet_;
  GameLoop* loop_;
};
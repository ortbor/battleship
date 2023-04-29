#pragma once


#include "common.hpp"

class Network {
 public:
  explicit Network(GameLoop* loop);
  Socket::Status SetOtherIP(IpAddress other_ip, size_t ip_port);
  void Send(std::string command_type, std::string coords = "");
  Command* GetCommand();

 protected:
  size_t port_;
  IpAddress other_ip_;
  TcpSocket socket_;
  TcpListener listener_;
  Packet packet_;
  GameLoop* loop_;
};

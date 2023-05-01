#pragma once

#include "common.hpp"

class Network {
 public:
  explicit Network(GameLoop* loop);
  Socket::Status UpdatePort(size_t port);
  void Terminate();
  void ServerAccept();
  void ServerConnect();
  Socket::Status ClientConnect(pair<IpAddress, size_t> address);
  void Send(std::string command_type, std::string coords = "");
  Command* GetCommand();

 protected:
  size_t port_ = 2000;
  TcpSocket socket_;
  TcpListener listener_;
  Packet packet_;
  Thread connect_thr;
  GameLoop* loop_;
};
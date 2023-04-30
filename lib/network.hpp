#pragma once

#include "common.hpp"

class Network {
 public:
  explicit Network(GameLoop* loop);
  void UpdatePort(size_t port);
  void Terminate();
  void ServerAccept();
  void ServerConnect();
  Socket::Status ClientConnect(pair<IpAddress, size_t> address);
  void Send(std::string command_type, std::string coords = "");
  void SetPort(size_t port);
  Command* GetCommand();

 protected:
  TcpSocket socket_;
  TcpListener listener_;
  Packet packet_;
  Thread connect_thr;
  GameLoop* loop_;
};
#pragma once

#include "common.hpp"

class Network {
 public:
  explicit Network(GameLoop* loop);
  size_t GetPort();
  Socket::Status UpdatePort(size_t port);
  void Terminate();
  Socket::Status ClientConnect(pair<IpAddress, size_t> address);
  void ServerAccept();
  void ServerConnect();
  void Disconnect(bool send = true);
  bool& GetConnected();

  void Send(string command_type, string coords = "");
  Command* GetCommand();

 private:
  TcpSocket m_socket;
  TcpListener m_listener;
  Thread m_connect_thr;
  GameLoop* m_loop;
  bool m_connected = false;
};

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
  void Send(std::string command_type, std::string coords = "");
  Command* GetCommand();

 protected:
  TcpSocket m_socket;
  TcpListener m_listener;
  Packet m_packet_in;
  Packet m_packet_out;
  Thread m_connect_thr;
  GameLoop* m_loop;
};

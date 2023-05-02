<<<<<<< HEAD
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
  TcpSocket socket_;
  TcpListener listener_;
  Packet packet_;
  Thread connect_thr;
  GameLoop* loop_;
};
||||||| 58d15e7
=======
#pragma once

#include "command.hpp"
#include "common.hpp"

class Network {
 public:
  explicit Network(GameLoop* loop);
  void Disconnect(bool send = true);
  bool Connected();
  size_t GetPort();
  Socket::Status UpdatePort(size_t port);
  void ClientAccept();
  void ClientConnect(const pair<IpAddress, size_t>& address);
  void ServerAccept();
  void ServerConnect();

  void Send(string command_type, string coords = "");
  Command* GetCommand();

 private:
  pair<IpAddress, size_t> m_address;
  TcpSocket m_socket;
  TcpListener m_listener;
  Thread m_client_thr;
  Thread m_server_thr;
  GameLoop* m_loop;
  DisconnectCommand terminate;
};
>>>>>>> dev-ntheme

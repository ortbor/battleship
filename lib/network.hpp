#pragma once

#include "common.hpp"
#include "game.hpp"
#include "button.hpp"
#include <SFML/Network.hpp>

class Network {
public:
    explicit Network(GameLoop* loop) : ip_(sf::IpAddress::getLocalAddress()), loop_(loop) {
      listener_.listen(2000);
    }
    void SetOtherIP(sf::IpAddress other_ip)  {
      other_ip_ = other_ip;
      socket_.connect(other_ip, 2000);
    }
    void Send(std::string command_type, std::string coords = "") {
      packet_ << command_type << coords;
      socket_.send(packet_);
      packet_.clear();
    }
    Command* GetCommand() {
      socket_.receive(packet_);
      std::string command_type;
      packet_ >> command_type;
      if (command_type == "add_ship") {
        return loop_->GetWindow()->GetButtons()["select_" + std::to_string(1 - loop_->GetLocalPlayer())]["ship"]->GetCommand();
      }
      std::string coords;
      packet_ >> coords;
      if (command_type == "add_cell") {
        return loop_->GetWindow()->GetButtons()["select_" + std::to_string(1 - loop_->GetLocalPlayer())]["cell" + coords]->GetCommand();
      }
      return loop_->GetWindow()->GetButtons()["play_" + std::to_string(1 - loop_->GetLocalPlayer())]["cell_rival" + coords]->GetCommand();
    }

protected:
    sf::IpAddress ip_, other_ip_;
    sf::TcpSocket socket_;
    sf::TcpListener listener_;
    sf::Packet packet_;
    GameLoop* loop_;
};
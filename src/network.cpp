#include "../lib/network.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/command.hpp"
#include "../lib/game.hpp"
#include "../lib/object.hpp"
#include "../lib/player.hpp"

Network::Network(GameLoop* loop)
    : ip_(sf::IpAddress::getLocalAddress()), loop_(loop) {
  listener_.listen(2000);
}

void Network::SetOtherIP(sf::IpAddress other_ip) {
  other_ip_ = other_ip;
  socket_.connect(other_ip, 2000);
}

void Network::Send(std::string command_type, std::string coords) {
  packet_ << command_type << coords;
  socket_.send(packet_);
  packet_.clear();
}

Command* Network::GetCommand() {
  socket_.receive(packet_);
  std::string command_type;
  packet_ >> command_type;
  if (command_type == "add_ship") {
    return loop_->GetWindow()
        .GetButtons()["select_" + std::to_string(1 - loop_->GetLocalPlayer())]
                     ["ship"]
        ->GetCommand()
        .get();
  }
  std::string coords;
  packet_ >> coords;
  if (command_type == "add_cell") {
    return loop_->GetWindow()
        .GetButtons()["select_" + std::to_string(1 - loop_->GetLocalPlayer())]
                     ["cell" + coords]
        ->GetCommand()
        .get();
  }
  return loop_->GetWindow()
      .GetButtons()["play_" + std::to_string(1 - loop_->GetLocalPlayer())]
                   ["cell_rival" + coords]
      ->GetCommand()
      .get();
}

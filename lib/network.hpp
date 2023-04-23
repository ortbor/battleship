#pragma once

#include <SFML/Network.hpp>
#include "common.hpp"
//#include "game.hpp"
//#include "button.hpp"

class Network {
public:
    explicit Network(GameLoop* loop);
    void SetOtherIP(sf::IpAddress other_ip);
    void Send(std::string command_type, std::string coords = "");
    Command* GetCommand();

protected:
    sf::IpAddress ip_, other_ip_;
    sf::TcpSocket socket_;
    sf::TcpListener listener_;
    sf::Packet packet_;
    GameLoop* loop_;
};
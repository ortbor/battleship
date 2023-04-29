#pragma once

#include "common.hpp"
#include "command.hpp"
#include "player.hpp"

class Game {
 public:
  Game(int length, int width);
  ~Game() = default;
  void Play();

 protected:
  bool finished_;
  std::array<Player, 2> players_;
  std::stack<Command> turns_;
  void SetAllShips(Player* player);
  void Link();
};


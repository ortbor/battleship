#pragma once

#include "cell.hpp"
#include "common.hpp"
#include "player.hpp"
#include "window.hpp"

class GameLoop {
 public:
  GameLoop(const Vector2f& size, size_t ships);
  ~GameLoop() = default;
  void Go();

  GameWindow* GetWindow();
  const size_t kShips = 10;

 protected:
  const Vector2f size_;
  array<Player, 2> players_;
  deque<Command*> turns_;
  GameWindow window_;
};

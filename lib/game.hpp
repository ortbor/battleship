#pragma once

#include "cell.hpp"
#include "common.hpp"
#include "player.hpp"
#include "window.hpp"
#include "network.hpp"
//#include "../src/network.cpp"

class GameLoop {
 public:
  GameLoop(const Vector2f& size, size_t ships);
  ~GameLoop() = default;
  void Go();
  void Clear();

  GameWindow& GetWnd();
  Network* GetNetwork();
  const Vector2f& GetSize() const;
  void Block();
  void Unblock();
  void SwitchBlock();
  bool IsBlocked() const;
  const string& GetBox() const;

  const size_t kShips = 10;

 protected:
  const Vector2f size_;
  array<Player, 2> players_;
  deque<Command*> turns_;
  GameWindow window_;
  Network network_;
  bool is_blocked_ = false;

  void ProcessNetwork();
};

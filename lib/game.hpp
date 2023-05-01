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
  Network& GetNetwork();
  void LaunckNetwork();
  void Terminate();
  const Vector2f& GetSize() const;
  bool& Blocked();
  const string& GetBox() const;
  int GetLocalPlayer() const;
  void SetLocalPlayer(int local_player);

  const size_t kShips = 10;

 protected:
  const Vector2f size_;
  array<Player, 2> players_;
  deque<Command*> turns_;
  GameWindow window_;
  Network network_;
  Thread network_thr_;
  bool is_blocked_ = false;
  int local_player_ = 0;

  void ProcessNetwork();
};

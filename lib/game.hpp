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

  GameWindow& GetWindow();
  Network* GetNetwork();
  int GetLocalPlayer() const;
  void SetLocalPlayer(int local_player);
  const Vector2f& GetSize() const;
  void Block();
  void Unblock();
  void SwitchBlock();
  bool IsBlocked() const;
  const string& GetIP() const;
  void AddToIP(char symbol);
  void RemoveLastIP();
  void CleanIP();

  const size_t kShips = 10;

 protected:
  const Vector2f size_;
  array<Player, 2> players_;
  deque<Command*> turns_;
  GameWindow window_;
  Network network_;
  bool is_blocked_ = false;
  int local_player_ = 0;
  string ip_ = "";

  void ProcessWindow();
  void ProcessNetwork();
};

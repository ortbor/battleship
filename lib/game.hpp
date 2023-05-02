#pragma once

#include "common.hpp"
#include "network.hpp"
#include "player.hpp"
#include "window.hpp"
#include "network.hpp"
//#include "../src/network.cpp"

class GameLoop {
 public:
  GameLoop(const Vector2u& size, size_t ships = 10);
  ~GameLoop() = default;
  void Go();
  void Clear();

<<<<<<< HEAD
  GameWindow& GetWnd();
  Network& GetNetwork();
  void LaunckNetwork();
  void Terminate();
  const Vector2f& GetSize() const;
  bool& Blocked();
  const string& GetBox() const;

  const size_t kShips = 10;
||||||| 58d15e7
  GameWindow* GetWindow();
  const size_t kShips = 10;
=======
  GameWindow& GetWnd();
  Network& GetNetwork();
  void LaunchNetwork();
  void Terminate();
  bool& GetBlocked();
  size_t GetLocalPlayer() const;
  void SetLocalPlayer(size_t local_player);
>>>>>>> dev-ntheme

<<<<<<< HEAD
 protected:
  const Vector2f size_;
  array<Player, 2> players_;
  deque<Command*> turns_;
  GameWindow window_;
  Network network_;
  Thread network_thr_;
  bool is_blocked_ = false;

  void ProcessNetwork();
||||||| 58d15e7
 protected:
  const Vector2f size_;
  array<Player, 2> players_;
  deque<Command*> turns_;
  GameWindow window_;
=======
  const size_t kShips;
  const Vector2u kSize;

 private:
  array<Player, 2> m_players;
  deque<Command*> m_turns;
  GameWindow m_window;
  Network m_network;
  Thread m_network_thr;
  size_t m_local_player = 0;
  bool m_blocked = false;

  void ProcessNetwork();
>>>>>>> dev-ntheme
};

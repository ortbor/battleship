#pragma once

#include "common.hpp"
#include "network.hpp"
#include "player.hpp"
#include "window.hpp"

class GameLoop {
 public:
  GameLoop(const Vector2u& size, size_t ships = 10);
  ~GameLoop() = default;
  void Go();
  void Clear();

  GameWindow& GetWnd();
  Network& GetNetwork();
  void LaunchNetwork();
  void Terminate();
  const Vector2u& GetSize() const;
  bool& Blocked();

  const size_t kShips;

 protected:
  const Vector2u m_size;
  array<Player, 2> m_players;
  deque<Command*> m_turns;
  GameWindow m_window;
  Network m_network;
  Thread m_network_thr;
  bool m_blocked = false;

  void ProcessNetwork();
};

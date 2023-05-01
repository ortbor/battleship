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
  size_t GetLocalPlayer() const;
  void SetLocalPlayer(size_t local_player);

  const size_t kShips;

 protected:
  const Vector2u m_size;
  array<Player, 2> m_players;
  deque<Command*> m_turns;
  GameWindow m_window;
  Network m_network;
  Thread m_network_thr;
  bool m_blocked = false;
  size_t m_local_player = 0;

  void ProcessNetwork();
};

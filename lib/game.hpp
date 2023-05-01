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
<<<<<<< HEAD
  size_t GetLocalPlayer() const;
  void SetLocalPlayer(size_t local_player);
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
=======
  const string& GetBox() const;
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)

  const size_t kShips = 10;

 protected:
<<<<<<< HEAD
  const Vector2u m_size;
  array<Player, 2> m_players;
  deque<Command*> m_turns;
  GameWindow m_window;
  Network m_network;
  Thread m_network_thr;
  bool m_blocked = false;
  size_t local_player_ = 0;
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
  const Vector2u m_size;
  array<Player, 2> m_players;
  deque<Command*> m_turns;
  GameWindow m_window;
  Network m_network;
  Thread m_network_thr;
  bool m_blocked = false;
=======
  const Vector2f size_;
  array<Player, 2> players_;
  deque<Command*> turns_;
  GameWindow window_;
  Network network_;
  Thread network_thr_;
  bool is_blocked_ = false;
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)

  void ProcessNetwork();
};

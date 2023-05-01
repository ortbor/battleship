#include "../lib/game.hpp"

#include "../lib/command.hpp"
#include "../lib/network.hpp"
#include "../lib/window.hpp"

GameLoop::GameLoop(const Vector2f& size, size_t ships)
    : kShips(ships),
      size_(size),
      players_(array<Player, 2>{Player(0, size), Player(1, size)}),
      window_(players_, size_),
      network_(this),
      network_thr_(&GameLoop::ProcessNetwork, this) {
  Command::loop_ = this;
  players_[0].LinkWithRival(&players_[1]);
}

void GameLoop::ProcessNetwork() {
<<<<<<< HEAD
  while (m_window.isOpen()) {
    m_network.GetCommand()->Execute(true);
||||||| 82297ec (Fixed a lot of bugs, added more new ones)
  while (m_window.isOpen()) {
    m_network.GetCommand()->Execute();
=======
  while (window_.isOpen()) {
    network_.GetCommand()->Execute();
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)
  }
}

void GameLoop::Go() {
  while (window_.isOpen()) {
    window_.GetCommand()->Execute();
  }
  network_thr_.terminate();
}

GameWindow& GameLoop::GetWnd() { return window_; }

Network& GameLoop::GetNetwork() { return network_; }

void GameLoop::LaunckNetwork() { network_thr_.launch(); }

void GameLoop::Terminate() { network_thr_.terminate(); }

const Vector2f& GameLoop::GetSize() const { return size_; }

bool& GameLoop::Blocked() { return is_blocked_; }

void GameLoop::Clear() {
  for (int pl = 0; pl < 2; ++pl) {
    players_[pl].Clear();
  }
}
<<<<<<< HEAD

GameWindow& GameLoop::GetWnd() { return m_window; }

Network& GameLoop::GetNetwork() { return m_network; }

void GameLoop::LaunchNetwork() { m_network_thr.launch(); }

void GameLoop::Terminate() { m_network_thr.terminate(); }

const Vector2u& GameLoop::GetSize() const { return m_size; }

bool& GameLoop::Blocked() { return m_blocked; }

size_t GameLoop::GetLocalPlayer() const { return local_player_; }

void GameLoop::SetLocalPlayer(size_t local_player) {
  local_player_ = local_player;
}
||||||| 82297ec (Fixed a lot of bugs, added more new ones)

GameWindow& GameLoop::GetWnd() { return m_window; }

Network& GameLoop::GetNetwork() { return m_network; }

void GameLoop::LaunchNetwork() { m_network_thr.launch(); }

void GameLoop::Terminate() { m_network_thr.terminate(); }

const Vector2u& GameLoop::GetSize() const { return m_size; }

bool& GameLoop::Blocked() { return m_blocked; }

=======
>>>>>>> parent of 82297ec (Fixed a lot of bugs, added more new ones)

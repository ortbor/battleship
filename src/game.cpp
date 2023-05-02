#include "../lib/game.hpp"

#include "../lib/command.hpp"
<<<<<<< HEAD
#include "../lib/network.hpp"
#include "../lib/window.hpp"
||||||| 58d15e7
#include "../lib/window.hpp"
=======
>>>>>>> dev-ntheme

GameLoop::GameLoop(const Vector2u& size, size_t ships)
    : kShips(ships),
<<<<<<< HEAD
      size_(size),
      players_(array<Player, 2>{Player(0, size), Player(1, size)}),
      window_(players_, size_),
      network_(this),
      network_thr_(&GameLoop::ProcessNetwork, this) {
  Command::loop_ = this;
  players_[0].LinkWithRival(&players_[1]);
||||||| 58d15e7
      size_(size),
      players_(array<Player, 2>{Player(0, size), Player(1, size)}),
      window_(players_, size_) {
  players_[0].LinkWithRival(&players_[1]);
=======
      kSize(size),
      m_players(array<Player, 2>{Player(0, size), Player(1, size)}),
      m_window(m_players, kSize),
      m_network(this),
      m_network_thr(&GameLoop::ProcessNetwork, this) {
  Command::m_loop = this;
  m_players[0].LinkWithRival(&m_players[1]);
}

void GameLoop::ProcessNetwork() {
  while (m_window.isOpen() && m_network.Connected()) {
    m_network.GetCommand()->Execute(true);
  }
>>>>>>> dev-ntheme
}

<<<<<<< HEAD
void GameLoop::ProcessNetwork() {
  while (window_.isOpen()) {
    network_.GetCommand()->Execute();
||||||| 58d15e7
void GameLoop::Go() {
  Command::loop_ = this;
  while (window_.isOpen()) {
    window_.GetCommand()->Execute();
=======
void GameLoop::Go() {
  while (m_window.isOpen()) {
    m_window.GetCommand()->Execute();
>>>>>>> dev-ntheme
  }
  m_network_thr.terminate();
}

<<<<<<< HEAD
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

||||||| 58d15e7
GameWindow* GameLoop::GetWindow() { return &window_; }

=======
>>>>>>> dev-ntheme
void GameLoop::Clear() {
  for (int pl = 0; pl < 2; ++pl) {
    m_players[pl].Clear();
  }
}

GameWindow& GameLoop::GetWnd() { return m_window; }

Network& GameLoop::GetNetwork() { return m_network; }

void GameLoop::LaunchNetwork() { m_network_thr.launch(); }

void GameLoop::Terminate() { m_network_thr.terminate(); }

bool& GameLoop::GetBlocked() { return m_blocked; }

size_t GameLoop::GetLocalPlayer() const { return m_local_player; }

void GameLoop::SetLocalPlayer(size_t local_player) {
  m_local_player = local_player;
}

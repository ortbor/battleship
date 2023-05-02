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
  while (window_.isOpen()) {
    network_.GetCommand()->Execute(true);
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


size_t GameLoop::GetLocalPlayer() const {
  return local_player_;
}

void GameLoop::SetLocalPlayer(size_t local_player) {
  local_player_ = local_player;
}


#include "../lib/game.hpp"

#include "../lib/command.hpp"
#include "../lib/network.hpp"
#include "../lib/window.hpp"

GameLoop::GameLoop(const Vector2f& size, size_t ships)
    : kShips(ships),
      size_(size),
      players_(array<Player, 2>{Player(0, size), Player(1, size)}),
      window_(players_, size_),
      network_(this) {
  players_[0].LinkWithRival(&players_[1]);
}

void GameLoop::ProcessNetwork() {
  while (window_.isOpen()) {
   network_.GetCommand()->Execute();
  }
}

void GameLoop::Go() {
  Command::loop_ = this;
  std::thread network_thread(&GameLoop::ProcessNetwork, this);
  while (window_.isOpen()) {
    window_.GetCommand()->Execute();
  }
}

GameWindow& GameLoop::GetWindow() { return window_; }

Network* GameLoop::GetNetwork() { return &network_; }

int GameLoop::GetLocalPlayer() const { return local_player_; }

void GameLoop::SetLocalPlayer(int local_player) {
  local_player_ = local_player;
}

const Vector2f& GameLoop::GetSize() const { return size_; }

void GameLoop::Block() { is_blocked_ = true; }

void GameLoop::Unblock() { is_blocked_ = false; }

void GameLoop::SwitchBlock() { is_blocked_ = !is_blocked_; }

bool GameLoop::IsBlocked() const { return is_blocked_; }

const string& GameLoop::GetIP() const { return ip_; }

void GameLoop::AddToIP(char symbol) { ip_ += symbol; }

void GameLoop::RemoveLastIP() {
  if (!ip_.empty()) {
    ip_.pop_back();
  }
}

void GameLoop::CleanIP() { ip_ = ""; }

void GameLoop::Clear() {
  for (int pl = 0; pl < 2; ++pl) {
    players_[pl].Clear();
  }
}

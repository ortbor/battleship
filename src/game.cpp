#include "../lib/game.hpp"

#include "../lib/command.hpp"
#include "../lib/window.hpp"

GameLoop::GameLoop(const Vector2f& size, size_t ships)
    : kShips(ships),
      size_(size),
      players_(array<Player, 2>{Player(0, size), Player(1, size)}),
      window_(players_, size_) {
  players_[0].LinkWithRival(&players_[1]);
}

void GameLoop::Go() {
  Command::loop_ = this;
  while (window_.isOpen()) {
    window_.GetCommand()->Execute();
  }
}

GameWindow* GameLoop::GetWindow() { return &window_; }

void GameLoop::Clear() {
  for (int pl = 0; pl < 2; ++pl) {
    players_[pl].Clear();
  }
}

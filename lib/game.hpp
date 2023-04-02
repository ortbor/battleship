#pragma once

#include "cell.hpp"
#include "common.hpp"
#include "player.hpp"
#include "window.hpp"


class GameLoop {
 public:
  GameLoop(const Vector2f& size);
  ~GameLoop();
  void Play();

 protected:
  const size_t kNumShips = 3;
  const size_t kCell = 65;
  const size_t kShiftX = 300;
  const size_t kShiftY = 270;

  bool finished_ = false;
  Vector2f size_;
  array<Player, 2> players_;
  stack<Command*> turns_;

  sf::Font font;
  GameWindow window;
  vector<sf::Drawable*> draw_;
  vector<Command*> command_;
  vector<vector<Button*>> buttons_;

  void SetAllShips(Player* player);
  void Link();
  void SetDraw();
  void SetCommands();
  void SetButtons();
  void Clear();
};

#pragma once

#include "cell.hpp"
#include "common.hpp"
#include "player.hpp"
#include "window.hpp"


class GameLoop {
 public:
  GameLoop(const Vector2f& size, size_t ships);
  ~GameLoop();
  void Play();

 protected:
  bool finished_ = false;
  const size_t ships_;
  const Vector2f size_;
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
};

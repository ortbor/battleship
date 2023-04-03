#pragma once

#include "cell.hpp"
#include "common.hpp"
#include "player.hpp"
#include "window.hpp"


class GameLoop {
 public:
  GameLoop(const Vector2f& size, size_t ships);
  ~GameLoop();
  void StartMenu();

 protected:
  bool back_ = false;
  const size_t ships_;
  const Vector2f size_;
  array<Player, 2> players_;
  vector<Command*> turns_;
  GameWindow window_;

  sf::Font font_;
  sf::Texture background_;
  vector<sf::Drawable*> draw_;
  vector<Command*> command_;
  vector<vector<Button*>> buttons_;

  void SetAllShips(Player* player);
  void Link();
  void Clear();
  void SetDraw();
  void SetCommands();
  void SetButtons();
  void Play();
  void Settings();
};

#pragma once

#include "cell.hpp"
#include "common.hpp"
#include "player.hpp"
#include "window.hpp"

class GameLoop {
  friend class AddCellCommand;
  friend class AddShipCommand;

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
  unordered_map<string, unordered_map<string, Button*>> buttons_;

  Text* GetText(const std::string& str, size_t size, const Color& color,
                const Vector2f& pos, int style = Text::Regular);
  RectangleShape* GetShape(const Vector2f& size, const Color& color,
                           const Vector2f& pos);
  void Link();
  void Clear();
  void SetButtons();
  void Play();
  void Settings();
  void Go();
};

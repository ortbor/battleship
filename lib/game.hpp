#pragma once

#include "cell.hpp"
#include "common.hpp"
#include "player.hpp"
#include "window.hpp"

class GameLoop {
  friend class AddCellCommand;
  friend class AddShipCommand;
  friend class ShootCommand;
  friend class SetButtonsCommand;

 public:
  GameLoop(const Vector2f& size, size_t ships);
  ~GameLoop();
  void Go();

 protected:
  const Vector2f size_;
  const size_t kShips = 10;
  array<Player, 2> players_;
  vector<Command*> turns_;
  GameWindow window_;

  sf::Font font_;
  sf::Texture background_;
  unordered_map<string, map<string, Button*>> buttons_;

  Text* GetText(const std::string& str, size_t size, const Color& color,
                const Vector2f& pos, int style = Text::Regular);
  static RectangleShape* GetShape(const Vector2f& size, const Color& color,
                           const Vector2f& pos);
  void Clear();
  void SetButtons();
};

#pragma once

#include "common.hpp"

class GameWindow : public sf::RenderWindow {
 public:
  GameWindow(const sf::String& title, Vector2f sides = {-1, -1});

  void Refresh();
  Command* GetCommand();
  void SetPlayer(Player* playern);
  void SetButtons(const unordered_map<string, Button*>& buttons);
  void DrawObjects();

 protected:
  Vector2f screen_;
  sf::View view_;
  Event event_;
  unordered_map<string, Button*> buttons_;
};

#pragma once

#include "common.hpp"

class GameWindow : public sf::RenderWindow {
 public:
  GameWindow(sf::String title, Vector2f sides = {-1, -1});

  void Refresh();
  Command* GetCommand();
  const vector<Button*>& GetButtons() const;
  void SetPlayer(Player* playern);
  void SetButtons(vector<Button*>& other);
  void DrawObjects();

 protected:
  Vector2f screen_;
  sf::View view_;
  Event event_;
  vector<Button*>* buttons_;
};

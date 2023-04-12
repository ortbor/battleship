#pragma once

#include "common.hpp"

class GameWindow : public sf::RenderWindow {
 public:
  GameWindow(const sf::String& title, array<Player, 2>& players,
             const Vector2f& size, Vector2f sides = {-1, -1});
  ~GameWindow();

  void Refresh();
  Command* GetCommand();
  void SetButtons(const string& str);
  void SetShow(const string& scene, const string& elem, bool show);
  void DrawObjects();
  void Configure(array<Player, 2>& players, const Vector2f& size);

 protected:
  Vector2f screen_ = Vector2f(VideoMode::getDesktopMode().width,
                              VideoMode::getDesktopMode().height);
  View view_;
  Event event_;

  Font font_;
  Texture background_;
  string button_str_ = "menu";
  unordered_map<string, map<string, Button*>> buttons_;

  Text* GetText(const std::string& str, size_t size, const Color& color,
                const Vector2f& pos, int style = Text::Regular);
  static RectangleShape* GetShape(const Vector2f& size, const Color& color,
                                  const Vector2f& pos);
};

#pragma once

#include "common.hpp"

class GameWindow : public sf::RenderWindow {
 public:
  GameWindow(array<Player, 2>& players, const Vector2f& size,
             Vector2f sides = {-1, -1});
  ~GameWindow();

  const std::unique_ptr<Command>& GetCommand();
  void SetButtons(const string& str);
  void SetShow(const string& scene, const string& elem, bool show);
  void DrawObjects();
  void SetVolume(Volume value);
  void Configure(array<Player, 2>& players, const Vector2f& size);

 protected:
  const std::string kName = "BATTLESH!P!!";
  const std::string kRes = "/share/battlesh1p/";
  const string kPath;
  const Vector2f screen_ = Vector2f(VideoMode::getDesktopMode().width,
                                    VideoMode::getDesktopMode().height);
  View view_;
  Event event_;

  Font font_;
  Texture background_;
  Music main_theme_;
  Music game_theme_;

  string button_str_ = "menu";
  unordered_map<string, map<string, std::unique_ptr<Button>>> buttons_;

  static std::filesystem::path Path();
  DrawObject GetText(const std::string& str, size_t size, const Color& color,
                     const Vector2f& pos, int style = Text::Regular,
                     bool show = true);
  static DrawObject GetShape(const Vector2f& size, const Color& color,
                             const Vector2f& pos, bool show = true);
};

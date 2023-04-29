#pragma once

#include "common.hpp"

class GameWindow : public sf::RenderWindow {
 public:
  GameWindow(array<Player, 2>& players, const Vector2f& size,
             Vector2f sides = {-1, -1});
  ~GameWindow();

  const std::shared_ptr<Command>& GetCommand();
  unordered_map<string, map<string, std::shared_ptr<Button>>>& GetButtons();
  Event& GetEvent();
  Music& GetMusic(const string& elem);
  string& GetBox();
  void SetButtons(const string& str);
  void SetObject(const string& scene, const string& elem, size_t index,
                 const string& str);
  void SetShow(const string& scene, const string& elem, size_t index,
               bool show);
  void DrawObjects();
  void SetVolume(Volume value);
  void Ficha();
  void Configure(array<Player, 2>& players, const Vector2f& size);

 protected:
  const std::string kName = "BATTLESH!P!!";
  const std::string kRes = "/share/battlesh1p/";
  const string kPath;
  const Vector2f screen_ = Vector2f(VideoMode::getDesktopMode().width,
                                    VideoMode::getDesktopMode().height);
  View view_;
  Event event_;

  sf::Font font_;
  Texture background_;
  Movie movie_;
  unordered_map<string, Music> music_;

  string text_box_ = "";
  string button_str_ = "menu";
  unordered_map<string, map<string, std::shared_ptr<Button>>> buttons_;

  static std::filesystem::path Path();
  DrawObject GetText(const std::string& str, size_t size, const Color& color,
                     const Vector2f& pos, int style = Text::Regular,
                     bool show = true);
  static DrawObject GetShape(const Vector2f& size, const Color& color,
                             const Vector2f& pos, bool show = true);
};

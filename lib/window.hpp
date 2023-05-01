#pragma once

#include "common.hpp"
#include "push.hpp"

class GameWindow : public sf::RenderWindow {
 public:
  GameWindow(array<Player, 2>& players, const Vector2u& size,
             Vector2u sides = {0, 0});
  ~GameWindow();

  const std::shared_ptr<Command>& GetCommand();
  Push& GetButtons();
  Event& GetEvent();
  Music& GetMusic(const string& elem);
  map<string, string>& GetBoxes();
  void SetButtons(const string& str);
  void SetObject(const string& scene, const string& elem, size_t index,
                 const string& str);
  void SetShow(const string& scene, const string& elem, size_t index,
               bool show);
  void DrawObjects();
  void SetVolume(CMDVolume type);
  void Ficha();

 protected:
  const std::string kRes = "/share/battlesh1p/";
  const Vector2f screen_ = Vector2f(VideoMode::getDesktopMode().width,
                                    VideoMode::getDesktopMode().height);
  View m_view;
  Event m_event;

  Font m_font;
  Texture m_background;
  Movie m_movie;
  map<string, Music> m_music;
  map<string, string> m_boxes;
  Push m_push;

  static std::filesystem::path Path();
};

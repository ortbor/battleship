#pragma once

#include "common.hpp"
#include "push.hpp"

class GameWindow : public sf::RenderWindow {
 public:
<<<<<<< HEAD
  GameWindow(array<Player, 2>& players, const Vector2f& size,
             Vector2f sides = {-1, -1});
||||||| 58d15e7
  GameWindow(array<Player, 2>& players,
             const Vector2f& size, Vector2f sides = {-1, -1});
=======
  GameWindow(array<Player, 2>& players, const Vector2u& size);
>>>>>>> dev-ntheme
  ~GameWindow();

<<<<<<< HEAD
  const std::shared_ptr<Command>& GetCommand();
  unordered_map<string, map<string, std::shared_ptr<Button>>>& GetButtons();
  Event& GetEvent();
  Music& GetMusic(const string& elem);
  string& GetBox();
||||||| 58d15e7
  Command* GetCommand();
=======
  const std::shared_ptr<Command>& GetCommand();
  Push& GetButtons();
  Event& GetEvent();
  Music& GetMusic(const string& elem);
  map<string, string>& GetBoxes();
>>>>>>> dev-ntheme
  void SetButtons(const string& str);
<<<<<<< HEAD
  void SetObject(const string& scene, const string& elem, size_t index,
                 const string& str);
  void SetShow(const string& scene, const string& elem, size_t index,
               bool show);
||||||| 58d15e7
  void SetShow(const string& scene, const string& elem, bool show);
=======
  void SetObject(const string& scene, const string& elem, size_t index,
                 const string& str);
  void SetShow(const string& scene, const string& elem, 
               bool show, int index = -1);
>>>>>>> dev-ntheme
  void DrawObjects();
<<<<<<< HEAD
  void SetVolume(Volume value);
  void Ficha();
  void Configure(array<Player, 2>& players, const Vector2f& size);
||||||| 58d15e7
  void Configure(array<Player, 2>& players, const Vector2f& size);
=======
  void SetVolume(CMDVolume type);
  void Ficha();
>>>>>>> dev-ntheme

<<<<<<< HEAD
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
||||||| 58d15e7
 protected:
  const std::string kName = "BATTLESH!P!!";
  const std::string kRes = "/share/battlesh1p/";

  Vector2f screen_ = Vector2f(VideoMode::getDesktopMode().width,
                              VideoMode::getDesktopMode().height);
  View view_;
  Event event_;

  Font font_;
  Texture background_;
  string button_str_ = "menu";
  unordered_map<string, map<string, Button*>> buttons_;

  static std::filesystem::path Path();
  Text* GetText(const std::string& str, size_t size, const Color& color,
                const Vector2f& pos, int style = Text::Regular);
  static RectangleShape* GetShape(const Vector2f& size, const Color& color,
                                  const Vector2f& pos);
=======
 private:
  View m_view;
  Event m_event;

  Movie m_movie;
  map<string, Music> m_music;
  map<string, string> m_boxes;
  Push m_push;
>>>>>>> dev-ntheme
};

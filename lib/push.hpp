#pragma once

#include "common.hpp"

class Push {
 public:
  Push() = default;

  template <typename Type, typename... Args>
  void Set(string scene, string obj, Args... param);

  const map<string, shared_ptr<Button>>& Data(const string& scene) const;
  Button* GetPressed(const string& scene, const Event& event);
  Button* Get(const string& scene, const string& obj);

  void Config(array<Player, 2>& players, const Vector2u& size, const Font& font,
              const Texture& background, const map<string, Music>& music,
              const map<string, string>& boxes);

 private:
  map<string, map<string, shared_ptr<Button>>> m_buttons;

  void ConfigMainMenu(const Font& font);
  void ConfigSettings(const Font& font, const map<string, Music>& music,
                      const map<string, string>& boxes);
  void ConfigVolume(const Font& font, const map<string, Music>& music);
  void ConfigPort(const Font& font, const map<string, string>& boxes);
  void ConfigPlayMenu(const Font& font);
  void ConfigClient(const Font& font);
  void ConfigServer(const Font& font);
  void ConfigField(array<Player, 2>& players, const Vector2u& size);
  void ConfigPlay(array<Player, 2>& players, const Font& font);
};

template <typename Type, typename... Args>
void Push::Set(string scene, string obj, Args... param) {
  if (scene == "any") {
    for (auto& scr : m_buttons) {
      scr.second[obj] = make_shared<Type>(param...);
    }
  } else {
    m_buttons[scene][obj] = make_shared<Type>(param...);
  }
}

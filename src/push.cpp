#include "../lib/push.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/command.hpp"
#include "../lib/object.hpp"
#include "../lib/player.hpp"

const map<string, shared_ptr<Button>>& Push::Data(const string& scene) const {
  return m_buttons.at(scene);
}

Button* Push::Get(const string& scene, const string& obj) {
  return m_buttons[scene][obj].get();
}

Button* Push::GetPressed(const string& scene, const Event& event) {
  for (auto& button : m_buttons[scene]) {
    if (button.second->IsPressed(event)) {
      return button.second.get();
    }
  }
  return nullptr;
}

void Push::Config(array<Player, 2>& players, const Vector2u& size,
                  const Font& font, const Texture& background,
                  const map<string, Music>& music,
                  const map<string, string>& boxes) {
  ConfigMainMenu(font);
  ConfigSettings(font, music, boxes);
  ConfigPlayMenu(font);
  ConfigClient(font);
  ConfigServer(font);
  ConfigField(players, size);
  ConfigPlay(players, font);

  Set<Button>("any", "close", make_shared<WindowCommand>(CMDType::Close));

  Set<Button>("any", "background", nullptr,
              DrawObject(make_shared<Sprite>(background)),
              TextObject(kName, 140, Color::Red, {475, 0}, font,
                         Text::Bold | Text::Underlined));
}

void Push::ConfigMainMenu(const Font& font) {
  Set<MouseButton>("menu", "play", Mouse::Left,
                   make_shared<SetSceneCommand>("play"),
                   RectObject({340, 150}, {0, 255, 95}, {790, 300}),
                   TextObject("Play", 140, Color::Red, {820, 270}, font));

  Set<MouseButton>("menu", "settings", Mouse::Left,
                   make_shared<SetSceneCommand>("settings"),
                   RectObject({530, 150}, {0, 255, 95}, {700, 820}),
                   TextObject("Settings", 140, Color::Red, {720, 790}, font));

  Set<MouseButton>("menu", "ficha", Mouse::Left,
                   make_shared<WindowCommand>(CMDType::Ficha),
                   RectObject({150, 150}, {0, 255, 95}, {1770, 930}, false));

  Set<MouseButton>("menu", "return", Mouse::Left,
                   make_shared<WindowCommand>(CMDType::Close),
                   RectObject({100, 100}, {0, 255, 95}, {70, 65}),
                   TextObject("X", 60, Color::Red, {97, 75}, font));
}

void Push::ConfigSettings(const Font& font, const map<string, Music>& music,
                          const map<string, string>& boxes) {
  Set<MouseButton>("settings", "return", Mouse::Left,
                   make_shared<SetSceneCommand>("menu"),
                   RectObject({100, 100}, {0, 255, 95}, {70, 65}),
                   TextObject("<-", 60, Color::Red, {85, 70}, font));

  ConfigVolume(font, music);
  ConfigPort(font, boxes);
}

void Push::ConfigVolume(const Font& font, const map<string, Music>& music) {
  Vector2u coord(370, 590);

  Set<Button>(
      "settings", "volume", nullptr,
      TextObject("Volume: " + bs::atos(music.at("main").getVolume()), 100,
                 Color::Red, {coord.x, coord.y}, font, Text::Bold));

  Set<MouseButton>(
      "settings", "vol_silence", Mouse::Left,
      make_shared<VolumeCommand>(CMDVolume::Silence),
      RectObject({100, 100}, {0, 255, 95}, {coord.x + 590, coord.y + 22}),
      TextObject("<X", 60, Color::Red, {coord.x + 592, coord.y + 32}, font));

  Set<MouseButton>(
      "settings", "vol_less", Mouse::Left,
      make_shared<VolumeCommand>(CMDVolume::Less),
      RectObject({100, 100}, {0, 255, 95}, {coord.x + 740, coord.y + 22}),
      TextObject("-", 60, Color::Red, {coord.x + 777, coord.y + 29}, font));

  Set<MouseButton>(
      "settings", "vol_more", Mouse::Left,
      make_shared<VolumeCommand>(CMDVolume::More),
      RectObject({100, 100}, {0, 255, 95}, {coord.x + 890, coord.y + 22}),
      TextObject("+", 60, Color::Red, {coord.x + 918, coord.y + 27}, font));

  Set<MouseButton>(
      "settings", "vol_max", Mouse::Left,
      make_shared<VolumeCommand>(CMDVolume::Max),
      RectObject({100, 100}, {0, 255, 95}, {coord.x + 1040, coord.y + 22}),
      TextObject("<))", 60, Color::Red, {coord.x + 1045, coord.y + 27}, font));
}

void Push::ConfigPort(const Font& font, const map<string, string>& boxes) {
  Vector2u coord(475, 300);

  Set<Button>("settings", "port", nullptr,
              TextObject("Change port: ", 100, Color::Red, {coord.x, coord.y},
                         font, Text::Bold));

  Set<KeyboardButton>(
      "settings", "port_box", make_shared<PortBoxCommand>(),
      RectObject({120, 70}, {200, 200, 200}, {coord.x + 608, coord.y + 35}),
      TextObject(boxes.at("port"), 40, Color::Black,
                 {coord.x + 618, coord.y + 43}, font));

  Set<MouseButton>(
      "settings", "port_save", Mouse::Left, make_shared<PortCommand>(),
      RectObject({150, 90}, {0, 255, 95}, {coord.x + 807, coord.y + 25}),
      TextObject("Save", 60, Color::Red, {coord.x + 820, coord.y + 27}, font));

  Set<Button>("settings", "port_status", nullptr,
              TextObject("Success", 80, Color::Green, {coord.x + 348, 445},
                         font, Text::Bold, false),
              TextObject("Invalid Port", 80, Color::Red, {coord.x + 260, 445},
                         font, Text::Bold, false),
              TextObject("Failed to set", 80, Color::Red, {coord.x + 258, 445},
                         font, Text::Bold, false));
}

void Push::ConfigPlayMenu(const Font& font) {
  Set<MouseButton>("play", "return", Mouse::Left,
                   make_shared<SetSceneCommand>("menu"),
                   RectObject({100, 100}, {0, 255, 95}, {70, 65}),
                   TextObject("<-", 60, Color::Red, {85, 70}, font));

  Set<MouseButton>(
      "play", "client", Mouse::Left, make_shared<SetSceneCommand>("client"),
      RectObject({665, 150}, {0, 255, 95}, {630, 300}),
      TextObject("Throw a glove", 100, Color::Red, {640, 300}, font));

  Set<MouseButton>(
      "play", "server", Mouse::Left, make_shared<IPServerCommand>(),
      RectObject({690, 150}, {0, 255, 95}, {615, 820}),
      TextObject("Wait for a shot", 100, Color::Red, {625, 823}, font));
}

void Push::ConfigClient(const Font& font) {
  Set<MouseButton>("client", "return", Mouse::Left,
                   make_shared<SetSceneCommand>("play"),
                   RectObject({100, 100}, {0, 255, 95}, {70, 65}),
                   TextObject("<-", 60, Color::Red, {85, 70}, font));

  Set<KeyboardButton>("client", "box", make_shared<IPBoxCommand>(),
                      RectObject({500, 70}, {200, 200, 200}, {708, 445}),
                      TextObject("", 40, Color::Black, {715, 450}, font));

  Set<MouseButton>("client", "save", Mouse::Left,
                   make_shared<IPClientCommand>(),
                   RectObject({260, 150}, {0, 255, 95}, {827, 600}),
                   TextObject("Save", 100, Color::Red, {857, 600}, font));

  Set<Button>("client", "status", nullptr,
              TextObject("Success", 80, Color::Green, {823, 800}, font,
                         Text::Bold, false),
              TextObject("Invalid IP", 80, Color::Red, {775, 800}, font,
                         Text::Bold, false),
              TextObject("Server is offline", 80, Color::Red, {660, 800}, font,
                         Text::Bold, false),
              TextObject("Connection timeout!", 80, Color::Red, {590, 800},
                         font, Text::Bold, false));
}

void Push::ConfigServer(const Font& font) {
  Set<MouseButton>("server", "return", Mouse::Left,
                   make_shared<TerminateCommand>(),
                   RectObject({100, 100}, {0, 255, 95}, {70, 65}),
                   TextObject("<-", 60, Color::Red, {85, 70}, font));

  Set<Button>("server", "status", nullptr,
              TextObject("Waiting for the connection...", 100, Color::Red,
                         {330, 490}, font, Text::Bold),
              TextObject("Connected!", 100, Color::Green, {700, 490}, font,
                         Text::Bold, false));
}

void Push::ConfigField(array<Player, 2>& players, const Vector2u& size) {
  for (size_t pl = 0; pl < 2; ++pl) {
    for (size_t i = 0; i < size.x; ++i) {
      for (size_t j = 0; j < size.y; ++j) {
        auto* cell_my = players[pl].GetMField()->GetCell(Vector2u(i, j));
        auto* cell_rv = players[pl].GetRField()->GetCell(Vector2u(i, j));
        auto play = "play_" + std::to_string(pl);
        auto cell = std::to_string(i * size.y + j);
        auto select = "select_" + std::to_string(pl);

        auto pos_my = Vector2u(140 + i * 70, 250 + j * 70);
        auto pos_rv = Vector2u(1080 + i * 70 - pl * 940, 250 + j * 70);
        Set<MouseButton>(
            select, "cell_m_" + cell, Mouse::Left,
            make_shared<AddCellCommand>(players.data() + pl, cell_my),
            RectObject({65, 65}, {255, 120, 255}, pos_my));
        Set<MouseButton>(
            play, "cell_r_" + cell, Mouse::Left,
            make_shared<ShootCommand>(players.data() + pl, cell_rv),
            RectObject({65, 65}, {255, 255, 255}, pos_rv));

        Set<Button>(play, "cell_m_" + cell, nullptr,
                    Get(select, "cell_m_" + cell)->GetShapes()[0]);

        auto rect_my = Get(select, "cell_m_" + cell)->GetShapes()[0];
        auto rect_rv = Get(play, "cell_r_" + cell)->GetShapes()[0];
        cell_my->SetShape(dynamic_cast<RectangleShape*>(rect_my.sprite.get()));
        cell_rv->SetShape(dynamic_cast<RectangleShape*>(rect_rv.sprite.get()));
      }
    }
  }
}

void Push::ConfigPlay(array<Player, 2>& players, const Font& font) {
  for (size_t pl = 0; pl < 2; ++pl) {
    auto play = "play_" + std::to_string(pl);
    auto select = "select_" + std::to_string(pl);
    Set<MouseButton>(
        select, "return", Mouse::Left, make_shared<SetSceneCommand>("play"),
        RectObject({100, 100}, {0, 255, 95}, {70, 65}),
        TextObject("<-", 60, Color::Red, {85, 70}, font),
        TextObject("Select your ships", 80, Color::Blue, {1110, 300}, font));

    Set<MouseButton>(select, "ship", Mouse::Left,
                     make_shared<AddShipCommand>(players.data() + pl),
                     RectObject({335, 110}, {0, 255, 95}, {1210, 530}),
                     TextObject("Add ship", 80, Color::Red, {1220, 530}, font));

    Set<MouseButton>(select, "return", Mouse::Left,
                     make_shared<SetSceneCommand>("play"),
                     RectObject({100, 100}, {0, 255, 95}, {70, 65}),
                     TextObject("<-", 60, Color::Red, {85, 72}, font));

    Set<Button>(select, "status", nullptr,
                TextObject("Success!", 80, Color::Green, {1240, 750}, font,
                           Text::Bold, false),
                TextObject("Cannot select\n    this cell!", 80, Color::Red,
                           {1120, 750}, font, Text::Bold, false),
                TextObject("Wrong shaped ship!", 80, Color::Red, {1030, 750},
                           font, Text::Bold, false));

    Set<MouseButton>(
        play, "return", Mouse::Left, make_shared<SetSceneCommand>("menu"),
        RectObject({100, 100}, {0, 255, 95}, {70, 65}),
        TextObject("<-", 60, Color::Red, {85, 72}, font),
        TextObject("Your turn ", 100, Color::Red, {675, 930}, font,
                   sf::Text::Bold),
        TextObject("Your field", 80, Color::Red, {133, 950}, font),
        TextObject("Rival field", 80, Color::Red, {1410, 950}, font));
  }

  Set<MouseButton>("won_0", "return", Mouse::Left,
                   make_shared<SetSceneCommand>("menu"),
                   RectObject({100, 100}, {0, 255, 95}, {70, 65}),
                   TextObject("<-", 60, Color::Red, {85, 70}, font),
                   TextObject("        Do you feel proud of yourself after\n"
                              "you killed all innocent other player's ships?..",
                              60, Color::Red, {360, 750}, font, Text::Bold));

  Set<MouseButton>(
      "won_1", "return", Mouse::Left, make_shared<SetSceneCommand>("menu"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 70}, font),
      TextObject("Rival win!", 120, Color::Red, {600, 350}, font, Text::Bold),
      TextObject("Don't worry, be happy!", 60, Color::Red, {360, 750}, font,
                 Text::Bold));
}

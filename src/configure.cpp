#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/object.hpp"
#include "../lib/player.hpp"
#include "../lib/window.hpp"
#include "command.cpp"

void GameWindow::Configure(array<Player, 2>& players, const Vector2f& size) {
  buttons_["menu"]["play"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("play"),
      RectObject({340, 150}, {0, 255, 95}, {790, 300}),
      TextObject("Play", 140, Color::Red, {820, 270}, font_));

  buttons_["menu"]["settings"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("settings"),
      RectObject({530, 150}, {0, 255, 95}, {700, 820}),
      TextObject("Settings", 140, Color::Red, {720, 790}, font_));

  buttons_["menu"]["ficha"] = std::make_shared<MouseButton>(
      Mouse::Button::Left,
      std::make_shared<ExecCommand>(*this, Event::MouseButtonPressed,
                                    [](GameWindow& window) { window.Ficha(); }),
      RectObject({150, 150}, {0, 255, 95}, {1770, 930}, false));

  buttons_["menu"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left,
      std::make_shared<ExecCommand>(*this, Event::MouseButtonPressed,
                                    [](GameWindow& window) { window.close(); }),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("X", 60, Color::Red, {97, 75}, font_));

  buttons_["settings"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("menu"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 70}, font_));

  buttons_["settings"]["volume"] = std::make_shared<Button>(
      nullptr,
      TextObject("Volume", 120, Color::Red, {430, 490}, font_, Text::Bold));

  buttons_["settings"]["vol_silence"] = std::make_shared<MouseButton>(
      Mouse::Button::Left,
      std::make_shared<ExecCommand>(
          *this, Event::MouseButtonPressed,
          [](GameWindow& window) { window.SetVolume(Volume::Silence); }),
      RectObject({100, 100}, {0, 255, 95}, {900, 530}),
      TextObject("<X", 60, Color::Red, {902, 540}, font_));

  buttons_["settings"]["vol_less"] = std::make_shared<MouseButton>(
      Mouse::Button::Left,
      std::make_shared<ExecCommand>(
          *this, Event::MouseButtonPressed,
          [](GameWindow& window) { window.SetVolume(Volume::Less); }),
      RectObject({100, 100}, {0, 255, 95}, {1050, 530}),
      TextObject("-", 60, Color::Red, {1090, 535}, font_));

  buttons_["settings"]["vol_more"] = std::make_shared<MouseButton>(
      Mouse::Button::Left,
      std::make_shared<ExecCommand>(
          *this, Event::MouseButtonPressed,
          [](GameWindow& window) { window.SetVolume(Volume::More); }),
      RectObject({100, 100}, {0, 255, 95}, {1200, 530}),
      TextObject("+", 60, Color::Red, {1228, 535}, font_));

  buttons_["settings"]["vol_max"] = std::make_shared<MouseButton>(
      Mouse::Button::Left,
      std::make_shared<ExecCommand>(
          *this, Event::MouseButtonPressed,
          [](GameWindow& window) { window.SetVolume(Volume::Max); }),
      RectObject({100, 100}, {0, 255, 95}, {1350, 530}),
      TextObject("<))", 60, Color::Red, {1355, 535}, font_));

  buttons_["play"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("menu"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 70}, font_));

  buttons_["play"]["connect"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("ip"),
      RectObject({665, 150}, {0, 255, 95}, {630, 300}),
      TextObject("Throw a glove", 100, Color::Red, {640, 300}, font_));

  buttons_["play"]["wait"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<ServerCommand>(),
      RectObject({1210, 150}, {0, 255, 95}, {360, 820}),
      TextObject("Wait for a dick to your ass", 100, Color::Red, {370, 820},
                 font_));

  buttons_["waiting"]["text"] = std::make_shared<Button>(
      nullptr, TextObject("Waiting for the connection...", 100, Color::Red,
                          {250, 490}, font_, Text::Bold));

  buttons_["ip"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("play"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 70}, font_));

  buttons_["ip"]["box"] = std::make_shared<KeyboardButton>(
      std::make_shared<IPBoxCommand>(),
      RectObject({500, 70}, {200, 200, 200}, {708, 445}),
      TextObject("", 40, Color::Black, {715, 450}, font_));

  buttons_["ip"]["save"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<ClientCommand>(),
      RectObject({260, 150}, {0, 255, 95}, {827, 600}),
      TextObject("Save", 100, Color::Red, {857, 600}, font_));

  buttons_["ip"]["status"] = std::make_shared<Button>(
      nullptr,
      TextObject("Success", 80, Color::Green, {823, 800}, font_, Text::Bold,
                 false),
      TextObject("Invalid IP", 80, Color::Red, {775, 800}, font_, Text::Bold,
                 false),
      TextObject("Server is offline", 80, Color::Red, {660, 800}, font_,
                 Text::Bold, false),
      TextObject("Connection timeout!", 80, Color::Red, {590, 800}, font_,
                 Text::Bold, false));

  buttons_["connect"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("play"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 70}, font_));

  buttons_["select_0"]["text"] = std::make_shared<Button>(
      nullptr,
      TextObject("Select your ships", 80, Color::Blue, {1110, 300}, font_));

  buttons_["select_0"]["ship"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<AddShipCommand>(players.data()),
      RectObject({335, 110}, {0, 255, 95}, {1210, 530}),
      TextObject("Add ship", 80, Color::Red, {1220, 530}, font_));

  buttons_["select_0"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("play"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 72}, font_));

  buttons_["select_0"]["status"] = std::make_shared<Button>(
      nullptr,
      TextObject("Success!", 80, Color::Green, {1240, 750}, font_, Text::Bold,
                 false),
      TextObject("Cannot select\n    this cell!", 80, Color::Red, {1120, 750},
                 font_, Text::Bold, false),
      TextObject("Wrong shaped ship!", 80, Color::Red, {1030, 750}, font_,
                 Text::Bold, false));

  buttons_["player_0"]["return"] = std::make_shared<MouseButton>(
      Mouse::Left, std::make_shared<SetCommand>("play"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 72}, font_));

  buttons_["player_0"]["turn"] = std::make_shared<Button>(
      nullptr, TextObject("Your turn ", 100, Color::Red, {675, 930}, font_,
                          sf::Text::Bold));

  buttons_["player_0"]["field_your"] = std::make_shared<Button>(
      nullptr, TextObject("Your field", 80, Color::Red, {133, 950}, font_));

  buttons_["player_0"]["field_rival"] = std::make_shared<Button>(
      nullptr, TextObject("Rival field", 80, Color::Red, {1410, 950}, font_));

  buttons_["won_0"]["text"] = std::make_shared<Button>(
      nullptr,
      TextObject("You win!", 120, Color::Red, {600, 350}, font_, Text::Bold),
      TextObject("        Do you feel proud of yourself after\n"
                 "you killed all innocent other player's ships?..",
                 60, Color::Red, {360, 750}, font_, Text::Bold));

  buttons_["won_0"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("menu"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 70}, font_));

  buttons_["won_1"]["text"] = std::make_shared<Button>(
      nullptr,
      TextObject("Rival win!", 120, Color::Red, {600, 350}, font_, Text::Bold),
      TextObject("Don't worry, be happy!", 60, Color::Red, {360, 750}, font_,
                 Text::Bold));

  buttons_["won_1"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("menu"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 70}, font_));

  for (size_t pl = 0; pl < 2; ++pl) {
    for (size_t i = 0; i < size.x; ++i) {
      for (size_t j = 0; j < size.y; ++j) {
        auto pos_my = Vector2f(140 + i * 70, 250 + j * 70);
        auto pos_rv = Vector2f(1080 + i * 70 - pl * 940, 250 + j * 70);
        std::string ind = std::to_string(i * size.y + j);
        auto* cell_my = players[pl].GetField()->GetCell(Vector2f(i, j));
        auto* cell_rv = players[pl].GetRField()->GetCell(Vector2f(i, j));

        buttons_["select_" + std::to_string(pl)]["cell" + ind] =
            std::make_shared<MouseButton>(
                Mouse::Button::Left,
                std::make_shared<AddCellCommand>(players.data() + pl, cell_my),
                RectObject({65, 65}, {255, 120, 255}, pos_my));

        buttons_["play_" + std::to_string(pl)]["cell_my" + ind] =
            std::make_shared<Button>(
                nullptr, buttons_["select_" + std::to_string(pl)]["cell" + ind]
                             .get()
                             ->GetDrawable()[0]);

        buttons_["play_" + std::to_string(pl)]["cell_rival" + ind] =
            std::make_shared<MouseButton>(
                Mouse::Button::Left,
                std::make_shared<ShootCommand>(players.data() + pl, cell_rv),
                RectObject({65, 65}, {255, 255, 255}, pos_rv));

        cell_my->SetShape(dynamic_cast<RectangleShape*>(
            buttons_["select_" + std::to_string(pl)]["cell" + ind]
                .get()
                ->GetDrawable()[0]
                .sprite.get()));

        cell_rv->SetShape(dynamic_cast<RectangleShape*>(
            buttons_["play_" + std::to_string(pl)]["cell_rival" + ind]
                .get()
                ->GetDrawable()[0]
                .sprite.get()));
      }
    }
  }

  for (auto& item : buttons_) {
    item.second["close"] =
        std::make_shared<Button>(std::make_shared<ExecCommand>(
            *this, Event::Closed, [](GameWindow& window) { window.close(); }));

    item.second["resize"] =
        std::make_shared<Button>(std::make_shared<ExecCommand>(
            *this, Event::Resized,
            [](GameWindow& window) { window.DrawObjects(); }));

    item.second["background"] = std::make_shared<Button>(
        nullptr, DrawObject(std::make_shared<Sprite>(background_)),
        TextObject(kName, 140, Color::Red, {475, 0}, font_,
                   Text::Bold | Text::Underlined));
  }
}

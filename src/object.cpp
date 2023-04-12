#include "../lib/button.hpp"
#include "../lib/game.hpp"
#include "command.cpp"

void GameLoop::Clear() {
  for (auto& scr : buttons_) {
    for (auto& item : scr.second) {
      delete item.second;
    }
  }
  buttons_.clear();
}

Text* GameLoop::GetText(const std::string& str, size_t size, const Color& color,
                        const Vector2f& pos, int style) {
  Text* title = new Text(str, font_, size);
  title->setFillColor(color);
  title->setPosition(pos);
  title->setStyle(style);
  return title;
}

RectangleShape* GameLoop::GetShape(const Vector2f& size, const Color& color,
                                   const Vector2f& pos) {
  sf::RectangleShape* box = new sf::RectangleShape(size);
  box->setFillColor(color);
  box->setPosition(pos);
  return box;
}

void GameLoop::SetButtons() {
  buttons_["menu"]["play"] = new MouseButton(
      Mouse::Button::Left, new SetButtonsCommand(&buttons_["select_0"]),
      {GetShape(Vector2f(340, 150), Color(0, 255, 95), Vector2f(790, 300)),
       GetText("Play", 140, Color::Red, {820, 270})});

  buttons_["menu"]["settings"] = new MouseButton(
      Mouse::Button::Left, new SetButtonsCommand(&buttons_["settings"]),
      {GetShape(Vector2f(530, 150), Color(0, 255, 95), Vector2f(700, 820)),
       GetText("Settings", 140, Color::Red, {720, 790})});

  buttons_["menu"]["return"] = new MouseButton(
      Mouse::Button::Left,
      new ExecCommand<GameWindow>(&window_, Event::Closed,
                                  [](GameWindow* window) { window->close(); }),
      {GetShape(Vector2f(100, 100), Color(0, 255, 95), Vector2f(70, 65)),
       GetText("X", 60, Color::Red, {97, 75})});

  buttons_["settings"]["return"] = new MouseButton(
      Mouse::Button::Left, new SetButtonsCommand(&buttons_["menu"]),
      {GetShape(Vector2f(100, 100), Color(0, 255, 95), Vector2f(70, 65)),
       GetText("<-", 60, Color::Red, {85, 70}),
       GetText("Nothing yet!", 140, Color::Red, {570, 530})});

  for (size_t pl = 0; pl < 2; ++pl) {
    buttons_["select_" + std::to_string(pl)]["text"] = new Button(
        nullptr, {GetText("Player " + std::to_string(pl + 1) +
                              ", select\n    your ships!",
                          80, Color::Blue, Vector2f(1110 - pl * 850, 300))});

    buttons_["select_" + std::to_string(pl)]["ship"] = new MouseButton(
        Mouse::Button::Left, new AddShipCommand(players_.data() + pl),
        {GetShape(Vector2f(335, 110), Color(0, 255, 95),
                  Vector2f(1210 - pl * 850, 550)),
         GetText("Add ship", 80, Color::Red, Vector2f(1220 - pl * 850, 550))});

    buttons_["select_" + std::to_string(pl)]["return"] = new MouseButton(
        Mouse::Button::Left, new SetButtonsCommand(&buttons_["menu"]),
        {GetShape(Vector2f(100, 100), Color(0, 255, 95), Vector2f(70, 65)),
         GetText("<-", 60, Color::Red, {85, 72})});

    for (size_t i = 0; i < size_.x; ++i) {
      for (size_t j = 0; j < size_.y; ++j) {
        auto pos_my = Vector2f(140 + i * 70 + pl * 940, 250 + j * 70);
        auto pos_rv = Vector2f(1080 + i * 70 - pl * 940, 250 + j * 70);
        std::string ind = std::to_string(i * size_.y + j);
        auto* cell_my = players_[pl].GetField()->GetCell(Vector2f(i, j));
        auto* cell_rv = players_[pl].GetRField()->GetCell(Vector2f(i, j));

        cell_my->SetShape(
            GetShape(Vector2f(65, 65), Color(255, 120, 255), pos_my));

        cell_rv->SetShape(
            GetShape(Vector2f(65, 65), Color(255, 120, 255), pos_rv));

        buttons_["select_" + std::to_string(pl)]["cell" + ind] =
            new MouseButton(Mouse::Button::Left,
                            new AddCellCommand(players_.data() + pl, cell_my),
                            {cell_my->GetShape()});

        buttons_["play_" + std::to_string(pl)]["cell_my" + ind] =
            new Button(nullptr, {cell_my->GetShape()});

        buttons_["play_" + std::to_string(pl)]["cell_rival" + ind] =
            new MouseButton(Mouse::Button::Left,
                            new ShootCommand(players_.data() + pl, cell_rv),
                            {cell_rv->GetShape()});
      }
    }

    buttons_["select_" + std::to_string(pl)]["ok"] =
        new Button(nullptr,
                   {GetText("Success!", 80, Color::Green,
                            Vector2f(1230 - pl * 850, 750), Text::Bold)},
                   false);

    buttons_["select_" + std::to_string(pl)]["errcell"] =
        new Button(nullptr,
                   {GetText("Cannot select\n    this cell!", 80, Color::Red,
                            Vector2f(1120 - pl * 850, 750), Text::Bold)},
                   false);

    buttons_["select_" + std::to_string(pl)]["errship"] =
        new Button(nullptr,
                   {GetText("Wrong shaped ship!", 80, Color::Red,
                            Vector2f(1030 - pl * 850, 750), Text::Bold)},
                   false);

    buttons_["play_" + std::to_string(pl)]["turn"] = new Button(
        nullptr, {GetText("Player " + std::to_string(pl + 1) + " turn ", 100,
                          Color::Red, {675, 930}, sf::Text::Bold)});

    buttons_["play_" + std::to_string(pl)]["field_my"] = new Button(
        nullptr,
        {GetText("My field", 80, Color::Red, Vector2f(133 + pl * 1200, 950))});

    buttons_["play_" + std::to_string(pl)]["field_rival"] =
        new Button(nullptr, {GetText("Rival field", 80, Color::Red,
                                     Vector2f(1410 - pl * 1200, 950))});

    buttons_["play_" + std::to_string(pl)]["return"] = new MouseButton(
        Mouse::Left, new SetButtonsCommand(&buttons_["menu"]),
        {GetShape(Vector2f(100, 100), Color(0, 255, 95), Vector2f(70, 65)),
         GetText("<-", 60, Color::Red, {85, 72})});
  }

  buttons_["starts"]["text"] =
      new Button(nullptr, {GetText("Game starts in infinity seconds!", 120,
                                   Color::Red, {150, 450})});

  for (auto& item : buttons_) {
    item.second["close"] = new Button(new ExecCommand<GameWindow>(
        &window_, Event::Closed, [](GameWindow* window) { window->close(); }));

    item.second["resize"] = new Button(new ExecCommand<GameWindow>(
        &window_, Event::Resized,
        [](GameWindow* window) { window->Refresh(); }));

    item.second["aaa, background, ponyaaaaatno!"] = new Button(
        nullptr,
        {new sf::Sprite(background_), GetText(kName, 140, Color::Red, {475, 0},
                                              Text::Bold | Text::Underlined)});
  }
}

#include "../lib/button.hpp"
#include "../lib/game.hpp"
#include "command.cpp"

void GameLoop::Clear() {
  for (auto& scr : buttons_) {
    for (auto& item : scr.second) {
      for (auto &draw : item.second->GetDrawable()) {
        delete draw;
      }
      delete item.second->GetCommand();
      delete item.second;
    }
  }
  buttons_.clear();
}

Text* GameLoop::GetText(const std::string& str, size_t size, const Color& color,
                        const Vector2f& pos, int style = Text::Regular) {
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
  buttons_["all"]["close"] = new Button(new ExecCommand<GameWindow>(
      &window_, Event::Closed, [](GameWindow* window) { window->close(); }));

  buttons_["all"]["resize"] = new Button(new ExecCommand<GameWindow>(
      &window_, Event::Closed, [](GameWindow* window) { window->Refresh(); }));

  buttons_["all"]["back"] = new MouseButton(
      Mouse::Button::Left,
      new ExecCommand<GameLoop>(this, Event::MouseButtonPressed,
                                [](GameLoop* game) { game->back_ = true; }),
      {GetShape(Vector2f(100, 100), Color(0, 255, 95), Vector2f(70, 65)),
       GetText("<-", 60, Color::Red, {85, 93})});

  buttons_["menu"]["background"] = new Button(
      nullptr,
      {new sf::Sprite(background_), GetText(kName, 140, Color::Red, {475, 0},
                                            Text::Bold | Text::Underlined)});

  buttons_["menu"]["exit"] = new MouseButton(
      Mouse::Button::Left,
      new ExecCommand<GameLoop>(this, Event::MouseButtonPressed,
                                [](GameLoop* game) { game->back_ = true; }),
      {GetShape(Vector2f(100, 100), Color(0, 255, 95), Vector2f(70, 65)),
       GetText("X", 60, Color::Red, {98, 75})});

  buttons_["menu"]["play"] = new MouseButton(
      Mouse::Button::Left,
      new ExecCommand<GameLoop>(this, Event::MouseButtonPressed,
                                [](GameLoop* game) { game->Play(); }),
      {GetShape(Vector2f(340, 150), Color(0, 255, 95), Vector2f(790, 300)),
       GetText("Play", 140, Color::Red, {820, 270})});

  buttons_["menu"]["settings"] = new MouseButton(
      Mouse::Button::Left,
      new ExecCommand<GameLoop>(this, Event::MouseButtonPressed,
                                [](GameLoop* game) { game->Settings(); }),
      {GetShape(Vector2f(530, 150), Color(0, 255, 95), Vector2f(700, 820)),
       GetText("Settings", 140, Color::Red, {720, 790})});

  buttons_["settings"]["go back!"] = new Button(
      nullptr, {GetText("Nothing yet!", 140, Color::Red, {570, 530})});

  for (size_t pl = 1; pl < 3; ++pl) {
    buttons_["select_" + std::to_string(pl)]["text"] = new Button(
        nullptr,
        {GetText("Player " + std::to_string(pl) + ", select\n    your ships!",
                 80, Color::Blue, {1960 - pl * 850, 300})});

    buttons_["select_" + std::to_string(pl)]["add"] = new MouseButton(
        Mouse::Button::Left, new AddShipCommand(players_.data()),
        {GetShape(Vector2f(335, 110), Color(0, 255, 95), Vector2f(1210, 550)),
         GetText("Add ship", 80, Color::Red, {2070 - pl * 850, 550})});

    for (size_t i = 0; i < size_.x; ++i) {
      for (size_t j = 0; j < size_.y; ++j) {
        players_[pl]
            .GetField()
            ->GetCell(Vector2f(i, j))
            ->SetShape(
                GetShape(Vector2f(65, 65), Color(255, 120, 255),
                         Vector2f(140 + i * 70 + pl * 940, 250 + j * 70)));

        players_[pl]
            .GetRField()
            ->GetCell(Vector2f(i, j))
            ->SetShape(GetShape(
                Vector2f(65, 65), Color(255, 120, 255),
                Vector2f(140 + i * 70 + (1 - pl) * 940, 250 + j * 70)));

        buttons_["select_" + std::to_string(pl)]["field"] = new MouseButton(
            Mouse::Button::Left,
            new AddCellCommand(
                players_.data() + pl,
                players_[pl].GetField()->GetCell(Vector2f(i, j))),
            {players_[pl].GetField()->GetCell(Vector2f(i, j))->GetShape()});

        buttons_["play_" + std::to_string(pl)]["field_my"] = new Button(
            nullptr,
            {players_[pl].GetField()->GetCell(Vector2f(i, j))->GetShape()});

        buttons_["play_" + std::to_string(pl)]["field_rival"] = new MouseButton(
            Mouse::Button::Left,
            new ShootCommand(players_.data() + pl,
                             players_[pl].GetRField()->GetCell(Vector2f(i, j))),
            {players_[pl].GetRField()->GetCell(Vector2f(i, j))->GetShape()});
      }
    }

    buttons_["select_" + std::to_string(pl) + "_ok"]["text"] =
        buttons_["select_" + std::to_string(pl)]["text"];

    buttons_["select_" + std::to_string(pl) + "_ok"]["add"] =
        buttons_["select_" + std::to_string(pl)]["add"];

    buttons_["select_" + std::to_string(pl) + "_ok"]["field"] =
        buttons_["select_" + std::to_string(pl)]["field"];

    buttons_["select_" + std::to_string(pl) + "_errcell"]["text"] =
        buttons_["select_" + std::to_string(pl)]["text"];

    buttons_["select_" + std::to_string(pl) + "_errcell"]["add"] =
        buttons_["select_" + std::to_string(pl)]["add"];

    buttons_["select_" + std::to_string(pl) + "_errcell"]["field"] =
        buttons_["select_" + std::to_string(pl)]["field"];

    buttons_["select_" + std::to_string(pl) + "_errship"]["text"] =
        buttons_["select_" + std::to_string(pl)]["text"];

    buttons_["select_" + std::to_string(pl) + "_errship"]["add"] =
        buttons_["select_" + std::to_string(pl)]["add"];

    buttons_["select_" + std::to_string(pl) + "_errship"]["field"] =
        buttons_["select_" + std::to_string(pl)]["field"];

    buttons_["select_" + std::to_string(pl) + "_ok"]["ok"] =
        new Button(nullptr, {GetText("Success!", 80, Color::Green,
                                     {2080 - pl * 850, 750}, Text::Bold)});

    buttons_["select_" + std::to_string(pl) + "_errcell"]["err"] = new Button(
        nullptr, {GetText("Cannot select\n    this cell!", 80, Color::Red,
                          {1970 - pl * 850, 750}, Text::Bold)});

    buttons_["select_" + std::to_string(pl) + "_errship"]["err"] =
        new Button(nullptr, {GetText("Wrong shaped ship!", 80, Color::Red,
                                     {1880 - pl * 850, 750}, Text::Bold)});

    buttons_["play_" + std::to_string(pl)]["turn"] = new Button(
        nullptr, {GetText("Player " + std::to_string(pl) + " turn ", 100,
                          Color::Red, {675, 930}, sf::Text::Bold)});

    buttons_["play_" + std::to_string(pl)]["field_my"] = new Button(
        nullptr, {GetText("My field", 80, Color::Red, {-717 + pl * 850, 950})});

    buttons_["play_" + std::to_string(pl)]["field_rival"] = new Button(
        nullptr,
        {GetText("Rival field", 80, Color::Red, {2260 - pl * 850, 950})});
  }

  buttons_["starts"]["text"] =
      new Button(nullptr, {GetText("Game starts in infinity seconds!", 120,
                                   Color::Red, {150, 450})});
}

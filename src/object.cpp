#include "../lib/button.hpp"
#include "../lib/game.hpp"
#include "command.cpp"

void GameLoop::Clear() {
  for (auto& item : draw_) {
    delete item;
  }
  for (auto& item : command_) {
    delete item;
  }
  for (auto& scr : buttons_) {
    for (auto& item : scr) {
      delete item;
    }
  }
  draw_.clear();
  command_.clear();
  buttons_.clear();
}

void GameLoop::SetDraw() {
  sf::Sprite* sprite = new sf::Sprite(background_);
  draw_.push_back(sprite);

  sf::Text* title = new sf::Text(kName, font_, 140);
  title->setFillColor(sf::Color::Red);
  title->setPosition(Vector2f(475, 0));
  title->setStyle(sf::Text::Bold | sf::Text::Underlined);
  draw_.push_back(title);

  sf::RectangleShape* next = new sf::RectangleShape(Vector2f(100, 100));
  next->setFillColor(sf::Color(0, 254, 95));
  next->setPosition(Vector2f(70, 65));
  draw_.push_back(next);

  title = new sf::Text("X", font_, 60);
  title->setFillColor(sf::Color::Red);
  title->setPosition(Vector2f(98, 75));
  draw_.push_back(title);

  next = new sf::RectangleShape(Vector2f(100, 100));
  next->setFillColor(sf::Color(0, 254, 95));
  next->setPosition(Vector2f(70, 65));
  draw_.push_back(next);

  title = new sf::Text("<-", font_, 60);
  title->setFillColor(sf::Color::Red);
  title->setPosition(Vector2f(85, 73));
  draw_.push_back(title);

  next = new sf::RectangleShape(Vector2f(340, 150));
  next->setFillColor(sf::Color(0, 254, 95));
  next->setPosition(Vector2f(790, 300));
  draw_.push_back(next);

  title = new sf::Text("Play", font_, 140);
  title->setFillColor(sf::Color::Red);
  title->setPosition(Vector2f(820, 270));
  draw_.push_back(title);

  next = new sf::RectangleShape(Vector2f(530, 150));
  next->setFillColor(sf::Color(0, 254, 95));
  next->setPosition(Vector2f(700, 820));
  draw_.push_back(next);

  title = new sf::Text("Settings", font_, 140);
  title->setFillColor(sf::Color::Red);
  title->setPosition(Vector2f(720, 790));
  draw_.push_back(title);

  title = new sf::Text("Nothing yet!", font_, 140);
  title->setFillColor(sf::Color::Red);
  title->setPosition(Vector2f(570, 530));
  draw_.push_back(title);

  std::string player("Player ");
  std::string select(", select\n    your ships!");
  for (size_t pl = 0; pl < 2; ++pl) {
    size_t shift = 850;
    title = new sf::Text(player + std::to_string(pl + 1) + select, font_, 80);
    title->setFillColor(sf::Color::Blue);
    title->setPosition(Vector2f(1110 - pl * shift, 300));
    draw_.push_back(title);

    next = new sf::RectangleShape(Vector2f(335, 110));
    next->setFillColor(sf::Color(0, 254, 95));
    next->setPosition(Vector2f(1210 - pl * shift, 550));
    draw_.push_back(next);

    title = new sf::Text("Add ship", font_, 80);
    title->setFillColor(sf::Color::Red);
    title->setPosition(Vector2f(1220 - pl * shift, 550));
    draw_.push_back(title);

    title = new sf::Text("Success!", font_, 80);
    title->setFillColor(sf::Color::Green);
    title->setPosition(Vector2f(1230 - pl * shift, 750));
    title->setStyle(sf::Text::Bold);
    draw_.push_back(title);

    title = new sf::Text("Cannot select\n    this cell!", font_, 80);
    title->setFillColor(sf::Color::Red);
    title->setPosition(Vector2f(1120 - pl * shift, 750));
    title->setStyle(sf::Text::Bold);
    draw_.push_back(title);

    title = new sf::Text("Wrong shaped ship!", font_, 80);
    title->setFillColor(sf::Color::Red);
    title->setPosition(Vector2f(1030 - pl * shift, 750));
    title->setStyle(sf::Text::Bold);
    draw_.push_back(title);

    title = new sf::Text(player + std::to_string(pl + 1) + "turn", font_, 100);
    title->setFillColor(sf::Color::Red);
    title->setPosition(Vector2f(675, 930));
    title->setStyle(sf::Text::Bold | sf::Text::Underlined);
    draw_.push_back(title);

    title = new sf::Text("My field", font_, 80);
    title->setFillColor(sf::Color::Red);
    title->setPosition(Vector2f(133 + pl * shift, 950));
    draw_.push_back(title);

    title = new sf::Text("Rival field", font_, 80);
    title->setFillColor(sf::Color::Red);
    title->setPosition(Vector2f(1410 - pl * shift, 950));
    draw_.push_back(title);
  }

  title = new sf::Text("Game starts in infinity seconds!", font_, 120);
  title->setFillColor(sf::Color::Red);
  title->setPosition(Vector2f(150, 450));
  draw_.push_back(title);

  for (size_t pl = 0; pl < 2; ++pl) {
    for (size_t i = 0; i < size_.x; ++i) {
      for (size_t j = 0; j < size_.y; ++j) {
        Vector2f size(65, 65);
        Vector2f left(140 + i * 70 + pl * 940, 250 + j * 70);
        sf::RectangleShape* cell = new sf::RectangleShape(size);
        players_[pl].GetField()->GetCell(Vector2f(i, j))->SetShape(cell);
        cell->setFillColor(sf::Color(255, 120, 255));
        cell->setPosition(left);
        draw_.push_back(cell);
      }
    }
    for (size_t i = 0; i < size_.x; ++i) {
      for (size_t j = 0; j < size_.y; ++j) {
        Vector2f size(65, 65);
        Vector2f left(140 + i * 70 + (1 - pl) * 940, 250 + j * 70);
        sf::RectangleShape* cell = new sf::RectangleShape(size);
        players_[pl].GetRField()->GetCell(Vector2f(i, j))->SetShape(cell);
        cell->setFillColor(sf::Color(255, 120, 255));
        cell->setPosition(left);
        draw_.push_back(cell);
      }
    }
  }
}

void GameLoop::SetCommands() {
  command_.push_back(new ExecCommand<GameWindow>(
      &window_, Event::Closed, [](GameWindow* window) { window->close(); }));
  command_.push_back(new ExecCommand<GameWindow>(
      &window_, Event::Resized, [](GameWindow* window) { window->Refresh(); }));
  command_.push_back(
      new ExecCommand<GameLoop>(this, Event::MouseButtonPressed,
                                [](GameLoop* game) { game->back_ = true; }));
  command_.push_back(new ExecCommand<GameLoop>(
      this, Event::MouseButtonPressed, [](GameLoop* game) { game->Play(); }));
  command_.push_back(
      new ExecCommand<GameLoop>(this, Event::MouseButtonPressed,
                                [](GameLoop* game) { game->Settings(); }));
  command_.push_back(new AddShipCommand(players_.data()));
  command_.push_back(new AddShipCommand(players_.data() + 1));

  for (size_t pl = 0; pl < 2; ++pl) {
    for (size_t i = 0; i < size_.x; ++i) {
      for (size_t j = 0; j < size_.y; ++j) {
        auto* cell = players_[pl].GetField()->GetCell(Vector2f(i, j));
        auto* cmd = new AddCellCommand(players_.data() + pl, cell);
        command_.push_back(cmd);
      }
    }

    for (size_t i = 0; i < size_.x; ++i) {
      for (size_t j = 0; j < size_.y; ++j) {
        auto* cell = players_[pl].GetRField()->GetCell(Vector2f(i, j));
        auto* cmd = new ShootCommand(players_.data() + pl, cell);
        command_.push_back(cmd);
      }
    }
  }
}

void GameLoop::SetButtons() {
  buttons_.resize(7);
  for (size_t scr = 0; scr < 7; ++scr) {
    buttons_[scr].push_back(new Button(command_[0], {draw_[0]}));
    buttons_[scr].push_back(new Button(command_[1], {draw_[1]}));
    size_t ind = 2 + (scr != 0) * 2;
    buttons_[scr].push_back(new MouseButton(Mouse::Button::Left, command_[2],
                                            {draw_[ind], draw_[ind + 1]}));
  }

  buttons_[0].push_back(
      new MouseButton(Mouse::Button::Left, command_[3], {draw_[6], draw_[7]}));
  buttons_[0].push_back(
      new MouseButton(Mouse::Button::Left, command_[4], {draw_[8], draw_[9]}));
  buttons_[1].push_back(new Button(nullptr, {draw_[10]}));

  size_t draw_l = 30;
  size_t cmd_l = 7;

  for (size_t pl = 0; pl < 2; ++pl) {
    auto* btn = new MouseButton(
        Mouse::Button::Left, command_[pl + 5],
        {draw_[12 + pl * 9], draw_[13 + pl * 9], draw_[11 + pl * 9]});
    buttons_[pl + 2].push_back(btn);
    for (size_t i = 0; i < 3; ++i) {
      buttons_[pl + 2].push_back(
          new Button(nullptr, {draw_[14 + pl * 9 + i]}, false));
    }
    for (size_t i = 0; i < 3; ++i) {
      buttons_[pl + 5].push_back(
          new Button(nullptr, {draw_[17 + pl * 9 + i]}));
    }

    for (size_t i = 0; i < size_.x; ++i) {
      for (size_t j = 0; j < size_.y; ++j) {
        size_t ind = pl * 2 * size_.x * size_.y + i * size_.y + j;
        btn = new MouseButton(Mouse::Button::Left, command_[ind + cmd_l],
                              {draw_[ind + draw_l]});
        buttons_[pl + 2].push_back(btn);
      }
    }
  }

  buttons_[4].push_back(
      new Button(nullptr, {draw_[draw_l - 1]}));

  for (size_t pl = 0; pl < 2; ++pl) {
    for (size_t i = 0; i < size_.x; ++i) {
      for (size_t j = 0; j < size_.y; ++j) {
        size_t ind = pl * size_.x * size_.y + i * size_.y + j;
        auto* btn =
            new MouseButton(Mouse::Button::Left, nullptr,
                            {draw_[ind + draw_l]});
        buttons_[5].push_back(btn);
      }
    }
    for (size_t i = 0; i < size_.x; ++i) {
      for (size_t j = 0; j < size_.y; ++j) {
        size_t ind = (pl * 2 + 1) * size_.x * size_.y + i * size_.y + j;
        auto* btn = new MouseButton(Mouse::Button::Left, command_[ind + cmd_l],
                                    {draw_[ind + draw_l]});
        buttons_[6].push_back(btn);
      }
    }
  }
}

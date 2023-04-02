#include "../lib/button.hpp"
#include "../lib/command.hpp"
#include "../lib/game.hpp"

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
  sf::Text* title = new sf::Text(kName, font, 140);
  title->setFillColor(sf::Color::Red);
  title->setPosition(Vector2f(475, 0));
  title->setStyle(sf::Text::Bold | sf::Text::Underlined);
  draw_.push_back(title);

  std::string player("Player ");
  std::string select(", select\n    your ships!");
  for (size_t i = 0; i < 2; ++i) {
    title = new sf::Text(player + std::to_string(i + 1) + select, font, 80);
    title->setFillColor(sf::Color::Blue);
    title->setPosition(Vector2f(1250, 300));
    draw_.push_back(title);
  }

  sf::RectangleShape* next = new sf::RectangleShape(Vector2f(335, 110));
  next->setFillColor(sf::Color(0, 254, 95));
  next->setPosition(Vector2f(1400, 700));
  draw_.push_back(next);

  title = new sf::Text("Add ship", font, 80);
  title->setFillColor(sf::Color::Red);
  title->setPosition(Vector2f(1410, 700));
  draw_.push_back(title);

  for (size_t pl = 0; pl < 2; ++pl) {
    for (size_t i = 0; i < size_.x; ++i) {
      for (size_t j = 0; j < size_.y; ++j) {
        Vector2f size(65, 65);
        Vector2f left(300 + i * 75, 270 + j * 75);
        sf::RectangleShape* cell = new sf::RectangleShape(size);
        players_[pl].GetField()->GetCell(Vector2f(i, j))->SetShape(cell);
        cell->setFillColor(sf::Color(255, 120, 255));
        cell->setPosition(left);
        draw_.push_back(cell);
      }
    }
  }

  title = new sf::Text("Game starts in infinity seconds!", font, 120);
  title->setFillColor(sf::Color::Red);
  title->setPosition(Vector2f(150, 450));
  draw_.push_back(title);
}

void GameLoop::SetCommands() {
  command_.push_back(new CloseCommand(&window));
  command_.push_back(new ResizeCommand(&window));
  command_.push_back(new AddShipCommand(players_.data(), &window));
  command_.push_back(new AddShipCommand(players_.data() + 1, &window));

  for (size_t pl = 0; pl < 2; ++pl) {
    for (size_t i = 0; i < size_.x; ++i) {
      for (size_t j = 0; j < size_.y; ++j) {
        auto* cell = players_[pl].GetField()->GetCell(Vector2f(i, j));
        auto* cmd =
            new AddCellToShipCommand(players_.data() + pl, &window, cell);
        command_.push_back(cmd);
      }
    }
  }
}

void GameLoop::SetButtons() {
  buttons_.resize(3);
  for (size_t scr = 0; scr < 3; ++scr) {
    buttons_[scr].push_back(new Button(command_[0], {draw_[0]}));
  }

  for (size_t pl = 0; pl < 2; ++pl) {
    Vector2f left(1400, 700);
    Vector2f right(1735, 910);
    auto coord = std::make_pair(left, right);
    auto* btn = new MouseButton(coord, Mouse::Button::Left, command_[pl + 2],
                                {draw_[3], draw_[4]});
    buttons_[pl].push_back(btn);
    buttons_[pl].push_back(new Button(command_[1], {draw_[pl + 1]}));

    for (size_t i = 0; i < size_.x; ++i) {
      for (size_t j = 0; j < size_.y; ++j) {
        left = Vector2f(300 + i * 75, 270 + j * 75);
        right = Vector2f(365 + i * 75, 335 + j * 75);
        coord = std::make_pair(left, right);
        size_t index = pl * size_.x * size_.y + i * size_.y + j;

        Command* cmd = command_[index + 4];
        btn = new MouseButton(coord, Mouse::Button::Left, cmd,
                              {draw_[index + 5]});
        buttons_[pl].push_back(btn);
      }
    }
  }
  size_t last = 2 * size_.x * size_.y + 5;

  buttons_[2].push_back(new Button(nullptr, {draw_[last]}));
}

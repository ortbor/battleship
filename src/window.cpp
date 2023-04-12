#include "../lib/window.hpp"

#include "../lib/button.hpp"
#include "../lib/command.hpp"
#include "../lib/player.hpp"

GameWindow::GameWindow(const sf::String& title, sf::Vector2f sides) {
  screen_ = Vector2f(sf::VideoMode::getDesktopMode().width,
                     sf::VideoMode::getDesktopMode().height);
  if (sides.x < 0) {
    sides.x = screen_.x;
    sides.y = screen_.y;
  }
  // view_.setSize(sides);
  create(sf::VideoMode(sides.x, sides.y), title, sf::Style::Fullscreen);
  // setView(view_);
}

void GameWindow::Refresh() {
  // view_.setCenter(Vector2f(view_.getSize().x / 2, view_.getSize().y / 2));
  // view_.setViewport(sf::FloatRect(0, 0, screen_.x / Vector2f(getSize()).x,
  //                                 screen_.x / Vector2f(getSize()).y));
  // setView(view_);
}

Command* GameWindow::GetCommand() {
  while (true) {
    waitEvent(event_);
    for (auto& button : *buttons_) {
      if (button.second->IsPressed(event_)) {
        return button.second->GetCommand();
      }
    }
  }
}

void GameWindow::SetButtons(map<string, Button*>* other) {
  buttons_ = other;
  DrawObjects();
}

void GameWindow::DrawObjects() {
  clear();
  for (const auto& item : *buttons_) {
    if (item.second->GetShow()) {
      for (const auto& object : item.second->GetDrawable()) {
        draw(*object);
      }
    }
  }
  display();
}

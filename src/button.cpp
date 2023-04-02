#include "../lib/button.hpp"

#include "../lib/command.hpp"

Button::Button(Command* commandn, const vector<sf::Drawable*>& drawn)
    : draw_(drawn), command_(commandn) {}

bool Button::IsPressed(const Event& event) const {
  return (event.type == Event::Closed &&
          dynamic_cast<CloseCommand*>(command_) != nullptr) ||
         (event.type == Event::Resized &&
          dynamic_cast<ResizeCommand*>(command_) != nullptr);
}

const vector<sf::Drawable*>& Button::GetDrawable() const { return draw_; }

Command* Button::GetCommand() { return command_; }

MouseButton::MouseButton(const pair<Vector2f, Vector2f>& coord,
                         const Mouse::Button& button, Command* command,
                         const vector<sf::Drawable*>& drawn)
    : Button(command, drawn), coord_(coord), button_(button) {}

bool MouseButton::IsPressed(const Event& event) const {
  return event.type == Event::MouseButtonPressed &&
         Inside(Vector2f(Mouse::getPosition())) &&
         Mouse::isButtonPressed(button_);
}

bool MouseButton::Inside(const Vector2f& mouse) const {
  return mouse.x >= coord_.first.x && mouse.x <= coord_.second.x &&
         mouse.y >= coord_.first.y && mouse.y <= coord_.second.y;
}

KeyboardButton::KeyboardButton(const Keyboard::Key& button, Command* command,
                               const vector<sf::Drawable*>& drawn)
    : Button(command, drawn), button_(button) {}

bool KeyboardButton::IsPressed(const Event& event) const {
  return event.type == Event::KeyPressed && Keyboard::isKeyPressed(button_);
}

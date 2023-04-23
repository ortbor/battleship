#include "../lib/button.hpp"

#include "../lib/command.hpp"

Button::Button(Command* commandn, const deque<sf::Drawable*>& drawn, bool show)
    : command_(commandn), draw_(drawn), show_(show) {}

bool Button::IsPressed(const Event& event,
                       const sf::RenderWindow& window) const {
  return command_ != nullptr && event.type == command_->GetType();
}

bool Button::GetShow() const { return show_; }

void Button::SetShow(bool show) { show_ = show; }

Command* Button::GetCommand() const { return command_; }

const deque<sf::Drawable*>& Button::GetDrawable() const { return draw_; }

MouseButton::MouseButton(const Mouse::Button& button, Command* command,
                         const deque<sf::Drawable*>& drawn)
    : Button(command, drawn), button_(button) {}

bool MouseButton::IsPressed(const Event& event,
                            const sf::RenderWindow& window) const {
  /*auto coord = Mouse::getPosition() - window.getPosition();
  float coeffx = 1920 / Vector2f(window.getSize()).x,
        coeffy = 1080 / Vector2f(window.getSize()).y;*/
  return command_ != nullptr && event.type == Event::MouseButtonPressed &&
         Inside(Vector2f(Mouse::getPosition())) && Mouse::isButtonPressed(button_);
}

bool MouseButton::Inside(const Vector2f& mouse) const {
  auto* shape = dynamic_cast<sf::RectangleShape*>(draw_[0]);
  if (shape == nullptr) {
    throw std::runtime_error("Is not a mouse button!");
    return false;
  }
  auto left = shape->getPosition();
  auto size = shape->getSize();
  auto right = Vector2f(left.x + size.x, left.y + size.y);
  return mouse.x >= left.x && mouse.x <= right.x && mouse.y >= left.y &&
         mouse.y <= right.y;
}

KeyboardButton::KeyboardButton(const Keyboard::Key& button, Command* command, const deque<sf::Drawable*>& drawn)
    : Button(command, drawn), button_(button) {}

bool KeyboardButton::IsPressed(const Event& event,
                               const sf::RenderWindow& window) const {
  return command_ != nullptr && event.type == Event::KeyPressed && Keyboard::isKeyPressed(button_);
}

#include "../lib/button.hpp"

#include "../lib/command.hpp"
#include "../lib/object.hpp"

bool Button::IsPressed(const Event& event) const {
  return command_ != nullptr && event.type == command_->GetType();
}

bool Button::GetShow() const { return show_; }

void Button::SetShow(bool show) { show_ = show; }

const std::unique_ptr<Command>& Button::GetCommand() const { return command_; }

const deque<DrawObject>& Button::GetDrawable() const { return draw_; }

bool MouseButton::IsPressed(const Event& event) const {
  /*auto coord = Mouse::getPosition() - window.getPosition();
  float coeffx = 1920 / Vector2f(window.getSize()).x,
        coeffy = 1080 / Vector2f(window.getSize()).y;*/
  return command_ != nullptr && event.type == Event::MouseButtonPressed &&
         Inside(Vector2f(Mouse::getPosition())) &&
         Mouse::isButtonPressed(button_);
}

bool MouseButton::Inside(const Vector2f& mouse) const {
  RectangleShape* shape = nullptr;
  if (draw_.empty() || (shape = dynamic_cast<RectangleShape*>(
                            draw_[0].sprite.get())) == nullptr) {
    return false;
  }

  auto left = shape->getPosition();
  auto size = shape->getSize();
  auto right = Vector2f(left.x + size.x, left.y + size.y);
  return mouse.x >= left.x && mouse.x <= right.x && mouse.y >= left.y &&
         mouse.y <= right.y;
}

bool KeyboardButton::IsPressed(const Event& event) const {
  return command_ != nullptr && event.type == Event::KeyPressed &&
         Keyboard::isKeyPressed(button_);
}

#include "../lib/button.hpp"

#include "../lib/command.hpp"
#include "../lib/object.hpp"

<<<<<<< HEAD
bool Button::IsPressed(const Event& event) const {
  return command_ != nullptr && event.type == command_->GetType();
||||||| 58d15e7
Button::Button(Command* commandn, const deque<sf::Drawable*>& drawn, bool show)
    : command_(commandn), draw_(drawn), show_(show) {}

bool Button::IsPressed(const Event& event,
                       const sf::RenderWindow& window) const {
  return command_ != nullptr && event.type == command_->GetType();
=======
bool Button::IsPressed(const Event& event) const {
  return m_cmd != nullptr && event.type == m_cmd->GetType();
>>>>>>> dev-ntheme
}

<<<<<<< HEAD
const std::shared_ptr<Command>& Button::GetCommand() const { return command_; }
||||||| 58d15e7
bool Button::GetShow() const { return show_; }
=======
const std::shared_ptr<Command>& Button::GetCommand() const { return m_cmd; }
>>>>>>> dev-ntheme

<<<<<<< HEAD
deque<DrawObject>& Button::GetDrawable() { return draw_; }
||||||| 58d15e7
void Button::SetShow(bool show) { show_ = show; }
=======
deque<DrawObject>& Button::GetShapes() { return m_draw; }
>>>>>>> dev-ntheme

<<<<<<< HEAD
bool MouseButton::IsPressed(const Event& event) const {
  /*auto coord = Mouse::getPosition() - window.getPosition();
  float coeffx = 1920 / Vector2f(window.getSize()).x,
        coeffy = 1080 / Vector2f(window.getSize()).y;*/
  return command_ != nullptr && event.type == Event::MouseButtonPressed &&
         Inside(Vector2f(Mouse::getPosition())) &&
         Mouse::isButtonPressed(button_);
||||||| 58d15e7
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
=======
bool MouseButton::IsPressed(const Event& event) const {
  return m_cmd != nullptr && event.type == Event::MouseButtonPressed &&
         Inside(Mouse::getPosition());
>>>>>>> dev-ntheme
}

<<<<<<< HEAD
bool MouseButton::Inside(const Vector2f& mouse) const {
  RectangleShape* shape = nullptr;
  if (draw_.empty() || (shape = dynamic_cast<RectangleShape*>(
                            draw_[0].sprite.get())) == nullptr) {
||||||| 58d15e7
bool MouseButton::Inside(const Vector2f& mouse) const {
  auto* shape = dynamic_cast<sf::RectangleShape*>(draw_[0]);
  if (shape == nullptr) {
    throw std::runtime_error("Is not a mouse button!");
=======
bool MouseButton::Inside(const Vector2i& mouse) const {
  RectangleShape* shape = nullptr;
  if (m_draw.empty() || (shape = dynamic_cast<RectangleShape*>(
                             m_draw[0].sprite.get())) == nullptr) {
>>>>>>> dev-ntheme
    return false;
  }

  auto left = shape->getPosition();
  auto size = shape->getSize();
  auto right = Vector2f(left.x + size.x, left.y + size.y);
  return mouse.x >= left.x && mouse.x <= right.x && mouse.y >= left.y &&
         mouse.y <= right.y;
}

<<<<<<< HEAD
bool KeyboardButton::IsPressed(const Event& event) const {
  return command_ != nullptr && event.type == Event::TextEntered;
||||||| 58d15e7
KeyboardButton::KeyboardButton(const Keyboard::Key& button, Command* command,
                               const deque<sf::Drawable*>& drawn)
    : Button(command, drawn), button_(button) {}

bool KeyboardButton::IsPressed(const Event& event,
                               const sf::RenderWindow& window) const {
  return command_ != nullptr && event.type == Event::KeyPressed &&
         Keyboard::isKeyPressed(button_);
=======
bool KeyboardButton::IsPressed(const Event& event) const {
  return m_cmd != nullptr && event.type == Event::TextEntered;
>>>>>>> dev-ntheme
}

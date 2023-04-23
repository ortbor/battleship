#pragma once

#include "common.hpp"

class Button {
 public:
  Button(Command* commandn, const deque<sf::Drawable*>& drawn = {},
         bool show = true);
  virtual ~Button() = default;

  virtual bool IsPressed(const Event& event,
                         const sf::RenderWindow& window) const;
  bool GetShow() const;
  void SetShow(bool show);
  Command* GetCommand() const;
  const deque<sf::Drawable*>& GetDrawable() const;

 protected:
  Command* command_;
  deque<sf::Drawable*> draw_;
  bool show_ = true;
};

class MouseButton final : public Button {
 public:
  MouseButton(const Mouse::Button& button, Command* command,
              const deque<sf::Drawable*>& drawn);

  bool IsPressed(const Event& event,
                 const sf::RenderWindow& window) const final;

 protected:
  Mouse::Button button_;

  bool Inside(const Vector2f& mouse) const;
};

class KeyboardButton final : public Button {
 public:
  KeyboardButton(const Keyboard::Key& button, Command* command,
                 const deque<sf::Drawable*>& drawn);

  bool IsPressed(const Event& event,
                 const sf::RenderWindow& window) const final;

protected:
    Keyboard::Key button_;
};

#pragma once

#include "common.hpp"

class Button {
 public:
  Button(Command* commandn, const vector<sf::Drawable*>& drawn ={}, bool show = true);
  virtual ~Button() = default;

  virtual bool IsPressed(const Event& event) const;
  bool GetShow() const;
  Command* GetCommand() const;
  const vector<sf::Drawable*>& GetDrawable() const;

 protected:
  Command* command_;
  vector<sf::Drawable*> draw_;
  bool show_ = true;
};

class MouseButton final : public Button {
 public:
  MouseButton(const Mouse::Button& button, Command* command,
              const vector<sf::Drawable*>& drawn);
  ~MouseButton() final = default;

  bool IsPressed(const Event& event) const final;

 protected:
  Mouse::Button button_;

  bool Inside(const Vector2f& mouse) const;
};

class KeyboardButton final : public Button {
 public:
  KeyboardButton(const Keyboard::Key& button, Command* command,
                 const vector<sf::Drawable*>& drawn);
  ~KeyboardButton() final = default;

  bool IsPressed(const Event& event) const final;

 protected:
  Keyboard::Key button_;
};

#pragma once

#include "common.hpp"

class Button {
 public:
  Button(Command* commandn, const vector<sf::Drawable*>& drawn);
  virtual ~Button() = default;

  virtual bool IsPressed(const Event& event) const;
  bool GetShow();
  void TurnShow();
  Command* GetCommand();
  const vector<sf::Drawable*>& GetDrawable() const;

 protected:
  bool show_ = true;
  vector<sf::Drawable*> draw_;
  Command* command_;
};

class MouseButton : public Button {
 public:
  MouseButton(const pair<Vector2f, Vector2f>& coord,
              const Mouse::Button& button, Command* command,
              const vector<sf::Drawable*>& drawn);
  ~MouseButton() final = default;

  bool IsPressed(const Event& event) const final;

 protected:
  pair<Vector2f, Vector2f> coord_;
  Mouse::Button button_;

  bool Inside(const Vector2f& mouse) const;
};

class KeyboardButton : public Button {
 public:
  KeyboardButton(const Keyboard::Key& button, Command* command,
                 const vector<sf::Drawable*>& drawn);
  ~KeyboardButton() final = default;

  bool IsPressed(const Event& event) const final;

 protected:
  Keyboard::Key button_;
};

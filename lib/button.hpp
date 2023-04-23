#pragma once

#include "common.hpp"

class Button {
 public:
  template <typename... Args>
  Button(std::unique_ptr<Command> command, Args... obj);
  virtual ~Button() = default;

  virtual bool IsPressed(const Event& event) const;
  bool GetShow() const;
  void SetShow(bool show);
  const std::unique_ptr<Command>& GetCommand() const;
  const deque<DrawObject>& GetDrawable() const;

 protected:
  unique_ptr<Command> command_;
  deque<DrawObject> draw_;
  bool show_ = true;
};

class MouseButton final : public Button {
 public:
  template <typename... Args>
  MouseButton(const Mouse::Button& button, std::unique_ptr<Command> command,
              Args... obj);

  bool IsPressed(const Event& event) const final;

 protected:
  Mouse::Button button_;

  bool Inside(const Vector2f& mouse) const;
};

class KeyboardButton final : public Button {
 public:
  template <typename... Args>
  KeyboardButton(const Keyboard::Key& button, std::unique_ptr<Command> command,
                 Args... obj);

  bool IsPressed(const Event& event) const final;

protected:
    Keyboard::Key button_;
};

template <typename... Args>
Button::Button(std::unique_ptr<Command> command, Args... obj)
    : command_(std::move(command)) {
  (..., draw_.push_back(std::move(obj)));
}

template <typename... Args>
MouseButton::MouseButton(const Mouse::Button& button,
                         std::unique_ptr<Command> command, Args... obj)
    : Button(std::move(command)), button_(button) {
  (..., draw_.push_back(std::move(obj)));
}

template <typename... Args>
KeyboardButton::KeyboardButton(const Keyboard::Key& button,
                               std::unique_ptr<Command> command, Args... obj)
    : Button(std::move(command)), button_(button) {
  (..., draw_.push_back(std::move(obj)));
}

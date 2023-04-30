#pragma once

#include "common.hpp"

class Button {
 public:
  template <typename... Args>
  Button(std::shared_ptr<Command> command, Args... obj);
  virtual ~Button() = default;

  virtual bool IsPressed(const Event& event) const;
  const std::shared_ptr<Command>& GetCommand() const;
  deque<DrawObject>& GetDrawable();

 protected:
  shared_ptr<Command> command_;
  deque<DrawObject> draw_;
};

class MouseButton final : public Button {
 public:
  template <typename... Args>
  MouseButton(const Mouse::Button& button, std::shared_ptr<Command> command,
              Args... obj);

  bool IsPressed(const Event& event) const final;

 protected:
  Mouse::Button button_;

  bool Inside(const Vector2f& mouse) const;
};

class KeyboardButton final : public Button {
 public:
  template <typename... Args>
  KeyboardButton(std::shared_ptr<Command> command, Args... obj);

  bool IsPressed(const Event& event) const final;
};

template <typename... Args>
Button::Button(std::shared_ptr<Command> command, Args... obj)
    : command_(std::move(command)) {
  (..., draw_.push_back(std::move(obj)));
}

template <typename... Args>
MouseButton::MouseButton(const Mouse::Button& button,
                         std::shared_ptr<Command> command, Args... obj)
    : Button(std::move(command)), button_(button) {
  (..., draw_.push_back(std::move(obj)));
}

template <typename... Args>
KeyboardButton::KeyboardButton(std::shared_ptr<Command> command, Args... obj)
    : Button(std::move(command)) {
  (..., draw_.push_back(std::move(obj)));
}

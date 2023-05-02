#pragma once

#include "common.hpp"

class Button {
 public:
<<<<<<< HEAD
  template <typename... Args>
  Button(std::shared_ptr<Command> command, Args... obj);
||||||| 58d15e7
  Button(Command* commandn, const deque<sf::Drawable*>& drawn = {},
         bool show = true);
=======
  template <typename... Args>
  Button(std::shared_ptr<Command> cmd, Args... obj);
>>>>>>> dev-ntheme
  virtual ~Button() = default;

<<<<<<< HEAD
  virtual bool IsPressed(const Event& event) const;
  const std::shared_ptr<Command>& GetCommand() const;
  deque<DrawObject>& GetDrawable();
||||||| 58d15e7
  virtual bool IsPressed(const Event& event,
                         const sf::RenderWindow& window) const;
  bool GetShow() const;
  void SetShow(bool show);
  Command* GetCommand() const;
  const deque<sf::Drawable*>& GetDrawable() const;
=======
  virtual bool IsPressed(const Event& event) const;
  const std::shared_ptr<Command>& GetCommand() const;
  deque<DrawObject>& GetShapes();
>>>>>>> dev-ntheme

 protected:
<<<<<<< HEAD
  shared_ptr<Command> command_;
  deque<DrawObject> draw_;
||||||| 58d15e7
  Command* command_;
  deque<sf::Drawable*> draw_;
  bool show_ = true;
=======
  shared_ptr<Command> m_cmd;
  deque<DrawObject> m_draw;
>>>>>>> dev-ntheme
};

class MouseButton final : public Button {
 public:
<<<<<<< HEAD
  template <typename... Args>
  MouseButton(const Mouse::Button& button, std::shared_ptr<Command> command,
              Args... obj);
||||||| 58d15e7
  MouseButton(const Mouse::Button& button, Command* command,
              const deque<sf::Drawable*>& drawn);
=======
  template <typename... Args>
  MouseButton(const Mouse::Button& btn, std::shared_ptr<Command> cmd,
              Args... obj);
>>>>>>> dev-ntheme

  bool IsPressed(const Event& event) const final;

 protected:
  Mouse::Button m_btn;

  bool Inside(const Vector2i& mouse) const;
};

class KeyboardButton final : public Button {
 public:
<<<<<<< HEAD
  template <typename... Args>
  KeyboardButton(std::shared_ptr<Command> command, Args... obj);
||||||| 58d15e7
  KeyboardButton(const Keyboard::Key& button, Command* command,
                 const deque<sf::Drawable*>& drawn);
=======
  template <typename... Args>
  KeyboardButton(std::shared_ptr<Command> cmd, Args... obj);
>>>>>>> dev-ntheme

  bool IsPressed(const Event& event) const final;
};
<<<<<<< HEAD

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
||||||| 58d15e7
=======

template <typename... Args>
Button::Button(std::shared_ptr<Command> cmd, Args... obj)
    : m_cmd(std::move(cmd)) {
  (..., m_draw.push_back(std::move(obj)));
}

template <typename... Args>
MouseButton::MouseButton(const Mouse::Button& btn,
                         std::shared_ptr<Command> cmd, Args... obj)
    : Button(std::move(cmd)), m_btn(btn) {
  (..., m_draw.push_back(std::move(obj)));
}

template <typename... Args>
KeyboardButton::KeyboardButton(std::shared_ptr<Command> cmd, Args... obj)
    : Button(std::move(cmd)) {
  (..., m_draw.push_back(std::move(obj)));
}
>>>>>>> dev-ntheme

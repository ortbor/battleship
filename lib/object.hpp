#pragma once

#include "common.hpp"

struct DrawObject {
  DrawObject() = default;
  DrawObject(shared_ptr<sf::Drawable> spriten);
  DrawObject(shared_ptr<sf::Drawable> spriten, bool shown);

  shared_ptr<sf::Drawable> sprite = nullptr;
  bool show = true;
};

struct TextObject : public DrawObject {
  TextObject(const string& str, size_t size, const Color& color,
             const Vector2f& pos, const sf::Font& font,
             int style = Text::Regular, bool show = true);
};

struct RectObject : public DrawObject {
  RectObject(const Vector2f& size, const Color& color, const Vector2f& pos,
             bool show = true);
};

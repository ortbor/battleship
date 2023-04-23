#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <array>
#include <deque>
#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>

using sf::Color;
using sf::Event;
using sf::Font;
using sf::Keyboard;
using sf::Mouse;
using sf::Music;
using sf::RectangleShape;
using sf::RenderWindow;
using sf::SoundBuffer;
using sf::Sprite;
using sf::Text;
using sf::Texture;
using sf::Vector2f;
using sf::Vector2u;
using sf::VideoMode;
using sf::View;
using std::array;
using std::deque;
using std::map;
using std::pair;
using std::string;
using std::unique_ptr;
using std::unordered_map;

class Cell;
class Ship;
class Field;
class MyField;
class RivalField;
class Player;
class Command;
class SetButtonsCommand;
class ExecCommand;
class CellCommand;
class AddCellCommand;
class AddShipCommand;
class ShootCommand;
class GameLoop;
class GameWindow;
struct DrawObject;
struct TextObject;
struct RectObject;
class Button;
class MouseButton;
class KeyboardButton;

enum class ShotResult { Kill, Harm, Miss, Unknown };
enum class State {
  Alive,
  Harmed,
  Missed,
  Clear,
  Unknown,
  Prohibited,
  Killed,
  Chosen
};

enum class Volume { Silence, Less, More, Max };
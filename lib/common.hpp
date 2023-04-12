#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <array>
#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
#include <unordered_map>
#include <deque>

using sf::Color;
using sf::Event;
using sf::Font;
using sf::Keyboard;
using sf::Mouse;
using sf::RectangleShape;
using sf::Text;
using sf::Texture;
using sf::Vector2f;
using sf::Vector2u;
using sf::VideoMode;
using sf::View;


using std::array;
using std::map;
using std::pair;
using std::string;
using std::unordered_map;
using std::deque;

class Cell;
class Ship;
class Field;
class MyField;
class RivalField;
class Player;
class Command;
class EmergencyCommand;
class AddCellToShipCommand;
class AddShipCommand;
class ShootCommand;
class GameLoop;
class GameWindow;
class Button;

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

static const std::string kName = "BATTLESH!P!!";
static const std::string kRes = "/share/battlesh1p/";
std::filesystem::path Path();
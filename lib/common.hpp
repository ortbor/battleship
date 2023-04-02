#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <array>
#include <filesystem>
#include <iostream>
#include <memory>
#include <stack>
#include <vector>

using sf::Event;
using sf::Keyboard;
using sf::Mouse;
using sf::Vector2f;
using sf::Vector2u;
using std::array;
using std::pair;
using std::stack;
using std::unique_ptr;
using std::vector;

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
static const std::string kResPrefix = "/share/battlesh1p_res/symbola.ttf";
std::filesystem::path Path();
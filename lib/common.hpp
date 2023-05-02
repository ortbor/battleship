#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <algorithm>
#include <array>
<<<<<<< HEAD
#include <deque>
||||||| 58d15e7
=======
#include <cmath>
#include <deque>
>>>>>>> dev-ntheme
#include <filesystem>
#include <iostream>
#include <map>
#include <memory>
<<<<<<< HEAD
#include <regex>
#include <sfeMovie/Movie.hpp>
||||||| 58d15e7
=======
#include <ranges>
#include <regex>
#include <sfeMovie/Movie.hpp>
>>>>>>> dev-ntheme
#include <unordered_map>

using sf::Color;
using sf::Event;
<<<<<<< HEAD
using sf::IpAddress;
||||||| 58d15e7
using sf::Font;
=======
using sf::Font;
using sf::IpAddress;
>>>>>>> dev-ntheme
using sf::Keyboard;
using sf::Mouse;
using sf::Music;
using sf::Packet;
using sf::RectangleShape;
<<<<<<< HEAD
using sf::RenderWindow;
using sf::Socket;
using sf::SoundBuffer;
using sf::Sprite;
using sf::TcpListener;
using sf::TcpSocket;
||||||| 58d15e7
=======
using sf::RenderWindow;
using sf::Socket;
using sf::SoundBuffer;
using sf::SoundSource;
using sf::Sprite;
using sf::TcpListener;
using sf::TcpSocket;
>>>>>>> dev-ntheme
using sf::Text;
using sf::Texture;
using sf::Thread;
using sf::Vector2f;
using sf::Vector2i;
using sf::Vector2u;
using sf::VideoMode;
using sf::View;
using sfe::Movie;
using std::array;
<<<<<<< HEAD
using std::deque;
||||||| 58d15e7
=======
using std::deque;
using std::make_shared;
>>>>>>> dev-ntheme
using std::map;
using std::pair;
using std::shared_ptr;
using std::string;
using std::unordered_map;

<<<<<<< HEAD
class Cell;
class Ship;
class Field;
class MyField;
class RivalField;
class Player;
class Command;
class SetCommand;
class ExecCommand;
class AddSymbolCommand;
class CellCommand;
class AddCellCommand;
class AddShipCommand;
class ShootCommand;
class GameLoop;
class GameWindow;
struct DrawObject;
struct TextObject;
struct RectObject;
||||||| 58d15e7
class Cell;
class Ship;
class Field;
class MyField;
class RivalField;
class Player;
class Command;
class SetButtonsCommand;
template <typename Type>
class ExecCommand;
class CellCommand;
class AddCellCommand;
class AddShipCommand;
class ShootCommand;
class GameLoop;
class GameWindow;
=======
>>>>>>> dev-ntheme
class Button;
class MouseButton;
class KeyboardButton;
class Network;

class Cell;
class Ship;
class Player;

class Command;
class IPBoxCommand;
class PortBoxCommand;
class IPServerCommand;
class IPClientCommand;
class PortCommand;
class VolumeCommand;
class DisconnectCommand;
class SetSceneCommand;
class CellCommand;
class AddCellCommand;
class ShootCommand;
class AddShipCommand;

class Field;
class MyField;
class RivalField;

class Push;
class Network;
class GameWindow;
class GameLoop;

struct DrawObject;
struct TextObject;
struct RectObject;

enum class CMDVolume { Silence, Less, More, Max };
enum class CMDType { Close, Ficha };
enum class ShotState { Kill, Harm, Miss, Unknown };
enum class CellState {
  Alive,
  Harmed,
  Missed,
  Clear,
  Unknown,
  Prohibited,
  Killed,
  Chosen
};
<<<<<<< HEAD

enum class Volume { Silence, Less, More, Max };
||||||| 58d15e7
=======

static const string kName = "BATTLESH!P!!";
static const string kRes = "/share/battlesh1p/";
static const size_t kMoveSleep = 700;

namespace bs {
string atos(long double num);
string Path();
}
>>>>>>> dev-ntheme

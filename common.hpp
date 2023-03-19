#pragma once

#include <algorithm>
#include <array>
#include <iostream>
#include <stack>
#include <vector>

class Cell;
class Ship;
class Field;
class MyField;
class RivalField;
class Player;
class Command;
class AddCellToShipCommand;
class AddShipCommand;
class ShootCommand;
class Game;

enum class ShotResult { Kill, Harm, Miss };
enum class State { Alive, Harmed, Missed, Clear, Unknown, Prohibited, Killed, Chosen };
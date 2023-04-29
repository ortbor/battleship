#pragma once

#include "common.hpp"
#include "ship.hpp"
#include "player.hpp"

class Command {
  friend class Player;
 public:
  Command(Player* player);
  virtual ~Command() = default;
  virtual void Execute() = 0;
  virtual void Undo() = 0;
  virtual bool IsValid() const = 0;

 protected:
  Player* player_;
};

class AddCellToShipCommand : public Command {
 public:
  ~AddCellToShipCommand() final = default;
  AddCellToShipCommand(Player* player, Cell* cell);
  void Execute() final;
  void Undo() final;
  bool IsValid() const final;
 protected:
  Cell* cell_;
};

class AddShipCommand : public Command {
 public:
  ~AddShipCommand() final = default;
  AddShipCommand(Player* player);
  void Execute() final;
  void Undo() final = 0;
  bool IsValid() const final;
};

class ShootCommand : public Command {
 public:
  ~ShootCommand() final = default;
  ShootCommand(Player* player, Cell* cell);
  void Execute() final;
  bool IsValid() const final;

 protected:
  Cell* cell_;
};
#pragma once

#include "common.hpp"

class Command {
  friend class Player;

 public:
  Command(Player* player, GameWindow* windown);
  virtual ~Command() = default;
  virtual bool Execute() = 0;

 protected:
  Player* player_;
  GameWindow* window_;

  virtual bool IsValid() const = 0;
};

class CloseCommand : public Command {
 public:
  CloseCommand(GameWindow* windown);
  ~CloseCommand() final = default;
  bool Execute() final;

 protected:
  bool IsValid() const final;
};

class ResizeCommand : public Command {
 public:
  ResizeCommand(GameWindow* windown);
  ~ResizeCommand() final = default;
  bool Execute() final;

 protected:
  bool IsValid() const final;
};

class AddCellToShipCommand : public Command {
 public:
  AddCellToShipCommand(Player* player, GameWindow* windown, Cell* cell);
  ~AddCellToShipCommand() final = default;
  bool Execute() final;
  bool IsValid() const final;

 protected:
  Cell* cell_;
};

class AddShipCommand : public Command {
 public:
  AddShipCommand(Player* player, GameWindow* windown);
  ~AddShipCommand() final = default;
  bool Execute() final;

 protected:
  bool IsValid() const final;
};

class ShootCommand : public Command {
 public:
  ShootCommand(Player* player, GameWindow* windown, Cell* cell);
  ~ShootCommand() final = default;
  bool Execute() final;

 protected:
  Cell* cell_;

  bool IsValid() const final;
};

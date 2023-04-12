#pragma once

#include "common.hpp"

class Command {
  friend class GameLoop;

 public:
  Command();
  Command(const Event::EventType& type);
  virtual ~Command() = default;

  virtual bool Execute() = 0;
  const Event::EventType& GetType();
  static GameLoop* loop_;

 protected:
  Event::EventType type_;
};

class SetButtonsCommand final : public Command {
 public:
  SetButtonsCommand(map<string, Button*>* buttons);
  ~SetButtonsCommand() final = default;

  bool Execute() final;

 private:
  map<string, Button*>* buttons_;
};

template <typename Type>
class ExecCommand final : public Command {
 public:
  ExecCommand(Type* obj, const Event::EventType& type_,
              void (*func)(Type* obj));
  ~ExecCommand() final = default;

  bool Execute() final;

 protected:
  Type* obj_;
  void (*func_)(Type* obj);
};

class CellCommand : public Command {
 public:
  CellCommand(Player* player, Cell* cell);
  ~CellCommand() override = default;
  virtual bool Execute() override = 0;

 protected:
  Player* player_;
  Cell* cell_;

  virtual bool IsValid() const = 0;
};

class AddCellCommand final : public CellCommand {
  friend class Player;

 public:
  AddCellCommand(Player* player, Cell* cell);
  ~AddCellCommand() final = default;
  bool Execute() final;

 protected:
  bool IsValid() const final;
};

class ShootCommand final : public CellCommand {
 public:
  ShootCommand(Player* player, Cell* cell);
  ~ShootCommand() final = default;
  bool Execute() final;

 protected:
  bool IsValid() const final;
};

class AddShipCommand : public Command {
 public:
  AddShipCommand(Player* player);
  ~AddShipCommand() = default;
  bool Execute() final;

 protected:
  Player* player_;

  bool IsValid() const;
};

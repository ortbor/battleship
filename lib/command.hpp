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

class AddSymbolCommand final : public Command {
 public:
  AddSymbolCommand() = default;
  ~AddSymbolCommand() final = default;

  bool Execute();
};

class SaveIPCommand final : public Command {
 public:
    SaveIPCommand() = default;
    ~SaveIPCommand() final = default;

    bool Execute();
};

class SetCommand final : public Command {
 public:
  SetCommand(const string& str);
  ~SetCommand() final = default;

  bool Execute() final;

 private:
  string str_;
};

class ExecCommand final : public Command {
 public:
  ExecCommand(GameWindow& obj, const Event::EventType& type,
              void (*func)(GameWindow& obj));
  ~ExecCommand() final = default;

  bool Execute() final;

 protected:
  GameWindow& obj_;
  void (*func_)(GameWindow& obj);
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
  virtual void Send() = 0;
};

class AddCellCommand final : public CellCommand {
  friend class Player;

 public:
  AddCellCommand(Player* player, Cell* cell);
  ~AddCellCommand() final = default;
  bool Execute() final;

 protected:
  bool IsValid() const final;
  void Send() final;
};

class ShootCommand final : public CellCommand {
 public:
  ShootCommand(Player* player, Cell* cell);
  ~ShootCommand() final = default;
  bool Execute() final;

 protected:
  bool IsValid() const final;
  void Send() final;
};

class AddShipCommand : public Command {
 public:
  AddShipCommand(Player* player);
  ~AddShipCommand() = default;
  bool Execute() final;

 protected:
  Player* player_;

  bool IsValid() const;
  static void Send();
};

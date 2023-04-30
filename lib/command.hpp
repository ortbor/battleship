#pragma once

#include "common.hpp"

class Command {
  friend class GameLoop;

 public:
  Command();
  Command(const Event::EventType& type);
  virtual ~Command() = default;

  virtual void Execute() = 0;
  const Event::EventType& GetType();
  static GameLoop* loop_;

 protected:
  Event::EventType type_;
};

class IPBoxCommand final : public Command {
 public:
  IPBoxCommand() = default;
  ~IPBoxCommand() final = default;

  void Execute();
};

class SaveIPCommand : public Command {
 public:
  SaveIPCommand() = default;
  ~SaveIPCommand() override = default;

  virtual void Execute() override = 0;

 protected:
  static std::string ip_num_r;
  static std::string ip_port_r;
  static std::string ip_str_r;
  static std::regex ip_regex;
};

class ServerCommand final : public SaveIPCommand {
 public:
  ServerCommand() = default;
  ~ServerCommand() final = default;

  void Execute();
};

class ClientCommand final : public SaveIPCommand {
 public:
  ClientCommand() = default;
  ~ClientCommand() final = default;

  void Execute();

 private:
  pair<string, size_t> ParseIp();
};

class TerminateCommand final : public Command {
 public:
  TerminateCommand() = default;
  ~TerminateCommand() final = default;

  void Execute();
};

class SetCommand final : public Command {
 public:
  SetCommand(const string& str);
  ~SetCommand() final = default;

  void Execute() final;

 private:
  string str_;
};

class ExecCommand final : public Command {
 public:
  ExecCommand(GameWindow& obj, const Event::EventType& type,
              void (*func)(GameWindow& obj));
  ~ExecCommand() final = default;

  void Execute() final;

 protected:
  GameWindow& obj_;
  void (*func_)(GameWindow& obj);
};

class CellCommand : public Command {
 public:
  CellCommand(Player* player, Cell* cell);
  ~CellCommand() override = default;
  virtual void Execute() override = 0;

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
  void Execute() final;

 protected:
  bool IsValid() const final;
  void Send() final;
};

class ShootCommand final : public CellCommand {
 public:
  ShootCommand(Player* player, Cell* cell);
  ~ShootCommand() final = default;
  void Execute() final;

 protected:
  bool IsValid() const final;
  void Send() final;
};

class AddShipCommand : public Command {
 public:
  AddShipCommand(Player* player);
  ~AddShipCommand() = default;
  void Execute() final;

 protected:
  Player* player_;

  bool IsValid() const;
  static void Send();
};

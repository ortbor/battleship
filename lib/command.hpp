#pragma once

#include "common.hpp"

class Command {
  friend class GameLoop;

 public:
  Command();
  Command(const Event::EventType& type);
  virtual ~Command() = default;

  virtual void Execute(bool is_remote = false) = 0;
  const Event::EventType& GetType();
  static GameLoop* loop_;

 protected:
  Event::EventType type_;
};

class IPBoxCommand final : public Command {
 public:
  IPBoxCommand() = default;
  ~IPBoxCommand() final = default;

  void Execute(bool is_remote = false);
};

class PortBoxCommand final : public Command {
public:
    PortBoxCommand() = default;
    ~PortBoxCommand() final = default;

    void Execute(bool is_remote = false);
};

class SaveIPCommand : public Command {
 public:
  SaveIPCommand() = default;
  ~SaveIPCommand() override = default;

  virtual void Execute(bool is_remote = false) override = 0;

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

  void Execute(bool is_remote = false);
};

class ClientCommand final : public SaveIPCommand {
 public:
  ClientCommand() = default;
  ~ClientCommand() final = default;

  void Execute(bool is_remote = false);

 private:
  pair<string, size_t> ParseIp();
};

class SavePortCommand final : public Command {
public:
    SavePortCommand() = default;
    ~SavePortCommand() final = default;

    void Execute(bool is_remote = false);

protected:
    static std::regex port_regex;
};

class TerminateCommand final : public Command {
   public:
    TerminateCommand() = default;
    ~TerminateCommand() final = default;

    void Execute(bool is_remote = false);
};

class SetCommand final : public Command {
 public:
  SetCommand(const string& str);
  ~SetCommand() final = default;

  void Execute(bool is_remote = false) final;

 private:
  string str_;
};

class ExecCommand final : public Command {
 public:
  ExecCommand(GameWindow& obj, const Event::EventType& type,
              void (*func)(GameWindow& obj));
  ~ExecCommand() final = default;

  void Execute(bool is_remote = false) final;

 protected:
  GameWindow& obj_;
  void (*func_)(GameWindow& obj);
};

class CellCommand : public Command {
 public:
  CellCommand(Player* player, Cell* cell);
  ~CellCommand() override = default;
  virtual void Execute(bool is_remote = false) override = 0;

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
  void Execute(bool is_remote = false) final;

 protected:
  bool IsValid() const final;
  void Send() final;
};

class ShootCommand final : public CellCommand {
 public:
  ShootCommand(Player* player, Cell* cell);
  ~ShootCommand() final = default;
  void Execute(bool is_remote = false) final;

 protected:
  bool IsValid() const final;
  void Send() final;
};

class AddShipCommand : public Command {
 public:
  AddShipCommand(Player* player);
  ~AddShipCommand() = default;
  void Execute(bool is_remote = false) final;

 protected:
  Player* player_;

  bool IsValid() const;
  static void Send();
};

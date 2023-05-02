#pragma once

#include "common.hpp"

class Command {
  friend class GameLoop;

 public:
  Command();
  Command(const Event::EventType& type);
  virtual ~Command() = default;

<<<<<<< HEAD
  virtual void Execute() = 0;
||||||| 58d15e7
  virtual bool Execute() = 0;
=======
  virtual void Execute(bool is_remote = false) = 0;
>>>>>>> dev-ntheme
  const Event::EventType& GetType();

 protected:
  static GameLoop* m_loop;
  Event::EventType m_type;
};

class IPBoxCommand final : public Command {
 public:
  IPBoxCommand() = default;
  ~IPBoxCommand() final = default;

<<<<<<< HEAD
  void Execute();
};

class PortBoxCommand final : public Command {
public:
    PortBoxCommand() = default;
    ~PortBoxCommand() final = default;

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

class SavePortCommand final : public Command {
public:
    SavePortCommand() = default;
    ~SavePortCommand() final = default;

    void Execute();

protected:
    static std::regex port_regex;
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
||||||| 58d15e7
  bool Execute() final;
=======
  void Execute(bool is_remote = false);
};

class PortBoxCommand final : public Command {
 public:
  PortBoxCommand() = default;
  ~PortBoxCommand() final = default;

  void Execute(bool is_remote = false);
};

class IPClientCommand final : public Command {
 public:
  IPClientCommand() = default;
  ~IPClientCommand() final = default;

  void Execute(bool is_remote = false);

  static std::string m_ip_port;
>>>>>>> dev-ntheme

 private:
  static std::string m_ip_addr;
  static std::string m_ip_full;
  static std::regex m_ip_regex;

  static pair<string, size_t> ParseIp();
};

<<<<<<< HEAD
class ExecCommand final : public Command {
||||||| 58d15e7
template <typename Type>
class ExecCommand final : public Command {
=======
class IPServerCommand final : public Command {
>>>>>>> dev-ntheme
 public:
<<<<<<< HEAD
  ExecCommand(GameWindow& obj, const Event::EventType& type,
              void (*func)(GameWindow& obj));
  ~ExecCommand() final = default;
||||||| 58d15e7
  ExecCommand(Type* obj, const Event::EventType& type_,
              void (*func)(Type* obj));
  ~ExecCommand() final = default;
=======
  IPServerCommand() = default;
  ~IPServerCommand() final = default;
>>>>>>> dev-ntheme

<<<<<<< HEAD
  void Execute() final;
||||||| 58d15e7
  bool Execute() final;
=======
  void Execute(bool is_remote = false);
};

class PortCommand final : public Command {
 public:
  PortCommand() = default;
  ~PortCommand() final = default;

  void Execute(bool is_remote = false);
>>>>>>> dev-ntheme

 protected:
<<<<<<< HEAD
  GameWindow& obj_;
  void (*func_)(GameWindow& obj);
||||||| 58d15e7
  Type* obj_;
  void (*func_)(Type* obj);
=======
  static std::regex m_port_regex;
};

class DisconnectCommand final : public Command {
 public:
  DisconnectCommand() = default;
  ~DisconnectCommand() final = default;

  void Execute(bool is_remote = false);
};

class VolumeCommand final : public Command {
 public:
  VolumeCommand(CMDVolume type);
  ~VolumeCommand() final = default;

  void Execute(bool is_remote = false);

 private:
  CMDVolume m_type;
};

class SetSceneCommand final : public Command {
 public:
  SetSceneCommand(const string& str);
  ~SetSceneCommand() final = default;

  void Execute(bool is_remote = false) final;

 private:
  static deque<string> m_stack;
  string m_str;
>>>>>>> dev-ntheme
};

class CellCommand : public Command {
 public:
  CellCommand(Player* player, Cell* cell);
  ~CellCommand() override = default;
<<<<<<< HEAD
  virtual void Execute() override = 0;
||||||| 58d15e7
  virtual bool Execute() override = 0;
=======
  virtual void Execute(bool is_remote = false) override = 0;
>>>>>>> dev-ntheme

 protected:
  Player* m_player;
  Cell* m_cell;

  virtual bool IsValid() const = 0;
  virtual void Send() = 0;
};

class AddCellCommand final : public CellCommand {
  friend class Player;

 public:
  AddCellCommand(Player* player, Cell* cell);
  ~AddCellCommand() final = default;
<<<<<<< HEAD
  void Execute() final;
||||||| 58d15e7
  bool Execute() final;
=======
  void Execute(bool is_remote = false) final;
>>>>>>> dev-ntheme

 protected:
  bool IsValid() const final;
  void Send() final;
};

class ShootCommand final : public CellCommand {
 public:
  ShootCommand(Player* player, Cell* cell);
  ~ShootCommand() final = default;
<<<<<<< HEAD
  void Execute() final;
||||||| 58d15e7
  bool Execute() final;
=======
  void Execute(bool is_remote = false) final;
>>>>>>> dev-ntheme

 protected:
  bool IsValid() const final;
  void Send() final;
};

class AddShipCommand : public Command {
 public:
  AddShipCommand(Player* player);
  ~AddShipCommand() = default;
<<<<<<< HEAD
  void Execute() final;
||||||| 58d15e7
  bool Execute() final;
=======
  void Execute(bool is_remote = false) final;
>>>>>>> dev-ntheme

 protected:
  Player* m_player;

  bool IsValid() const;
  static void Send();
};

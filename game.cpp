#include "game.hpp"

Game::Game(int length, int width)
    : finished_(false),
      players_(std::array<Player, 2>{Player(0, length, width),
                                     Player(1, length, width)}) {
  Link();
}

void Game::Link() { players_[0].LinkWithRival(&players_[1]); }

void Game::SetAllShips(Player* player) {
  std::cout << "Player " << player->GetIndex() + 1 << ", set your ships.\n";
  for (int i = 0; i < 10; ++i) {
    std::cout << "Insert ship.\n";
    bool ship_set = false;
    std::stack<Command*> command_stack;
    while (!ship_set) {
    /*  Command* command = window.GetButton()->GetCommand();
      if (command->IsValid()) {
        command->Execute();
        if (typeid(command) == typeid(AddCellToShipCommand)) {
          command_stack.push(command);
          turns_.push(command);
        }
        if (typeid(command) == typeid(AddShipCommand)) {
          turns_.push(command);
          player->FinishSettingShip();
          ship_set = true;
        }
      } else {
        if (typeid(command) == typeid(AddShipCommand)) {
          while (!command_stack.empty()) {
            command_stack.top()->Undo();
            command_stack.pop();
          }
        }
        std::cout << "Error. Try again.\n";
      }*/
    }
  }
}

void Game::Play() {
  for (int i = 0; i <= 1; ++i) {
    Game::SetAllShips(&players_[i]);
  }
  int current_player_index = 0;
  Player* current_player = &players_[0];
  Player* current_rival = &players_[1];
  while (!finished_) {
    bool executed = false;
    /*while (!executed) {
      Command* command = window.GetButton()->GetCommand();
      if (command->IsValid() && typeid(command) != typeid(AddShipCommand)
          && typeid(command) != typeid(AddCellToShipCommand)) {
        command->Execute();
        if (typeid(command) == typeid(ShootCommand)) {
          turns_.push(command);
          executed = true;
        }
      } else {
        std::cout << "Error. Try again.\n";
      }
    }*/
    if (current_rival->GetShipCount() == 0) {
      finished_ = true;
      std::cout << "Player " << current_player_index + 1 << " won.\n";
    }
    if (current_player->GetLastShotResult() == ShotResult::Miss) {
      current_rival = &players_[current_player_index];
      current_player_index = 1 - current_player_index;
      current_player = &players_[current_player_index];
    }
  }
}
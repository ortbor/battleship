#include "../lib/game.hpp"

#include "../lib/cell.hpp"
#include "../lib/command.hpp"
#include "../lib/window.hpp"

GameLoop::GameLoop(const Vector2f& size, size_t ships)
    : ships_(ships),
      size_(size),
      players_(std::array<Player, 2>{Player(0, size), Player(1, size)}),
      window(kName) {
  Link();
  SetDraw();
  SetCommands();
  SetButtons();
}

GameLoop::~GameLoop() { Clear(); }

void GameLoop::Link() { players_[0].LinkWithRival(&players_[1]); }

void GameLoop::SetAllShips(Player* player) {
  for (size_t i = 0; i < ships_; ++i) {
    stack<AddCellToShipCommand*> command_stack;
    while (true) {
      Command* command = window.GetCommand();
      if (command->Execute()) {
        if (!window.isOpen()) {
          return;
        }

        auto* add_cell_command = dynamic_cast<AddCellToShipCommand*>(command);
        if (add_cell_command != nullptr) {
          command_stack.push(add_cell_command);
          turns_.push(command);
        }

        auto* add_ship_command = dynamic_cast<AddShipCommand*>(command);
        if (add_ship_command != nullptr) {
          turns_.push(command);
          for (; !command_stack.empty(); command_stack.pop()) {
            std::cout << "F" << command_stack.size() << ' ';
          }
          break;  
        }
      } else {
        
      }
    }
  }
}

void GameLoop::Play() {
  Player* current_player = players_.data();
  Player* current_rival = &players_[1];
  for (int i = 0; i < 2; ++i) {
    window.SetPlayer(&players_[i]);
    window.SetButtons(buttons_[i]);
    window.DrawObjects();

    SetAllShips(&players_[i]);
    if (!window.isOpen()) {
      return;
    }
  }

  window.SetButtons(buttons_[2]);
  window.DrawObjects();

  int current_player_index = 0;
  while (!finished_) {
    bool executed = false;
    while (!executed) {
      Command* command = window.GetCommand();
      if (!window.isOpen()) {
        return;
      }
      if (command->Execute() && typeid(command) != typeid(AddShipCommand) &&
          typeid(command) != typeid(AddCellToShipCommand)) {
        if (typeid(command) == typeid(ShootCommand)) {
          turns_.push(command);
          executed = true;
        }
        continue;
      }
      std::cout << "Error. Try again.\n";
    }
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

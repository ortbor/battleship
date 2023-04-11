#include "../lib/game.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/command.hpp"
#include "../lib/window.hpp"

GameLoop::GameLoop(const Vector2f& size, size_t ships)
    : ships_(ships),
      size_(size),
      players_(std::array<Player, 2>{Player(0, size), Player(1, size)}),
      window_(kName) {
  if (!font_.loadFromFile(Path().string() + kRes + "symbola.ttf")) {
    throw std::runtime_error("Cannot load font");
  }
  if (!background_.loadFromFile(Path().string() + kRes + "background.jpg")) {
    throw std::runtime_error("Cannot load background");
  }

  Link();
  SetButtons();
}

GameLoop::~GameLoop() { Clear(); }

void GameLoop::Link() { players_[0].LinkWithRival(&players_[1]); }

void GameLoop::StartMenu() {
  while (window_.isOpen() && !back_) {
    window_.SetButtons(buttons_[0]);
    window_.DrawObjects();
    window_.GetCommand()->Execute();
  }
}

void GameLoop::Play() {
  for (size_t pl = 0; pl < 2; ++pl) {
    while (players_[pl].GetShipCount() < ships_) {
      window_.SetButtons(buttons_[2 + pl]);
      window_.DrawObjects();
      auto* command = window_.GetCommand();
      auto* add_ship_command = dynamic_cast<AddShipCommand*>(command);

      if (command->Execute()) {
        if (!window_.isOpen() || back_) {
          back_ = false;
          return;
        }
        buttons_[pl + 2][5]->SetShow(false);
        buttons_[pl + 2][6]->SetShow(false);
        if (add_ship_command != nullptr) {
          buttons_[pl + 2][4]->SetShow(true);
        }
      } else {
        buttons_[pl + 2][4]->SetShow(false);
        auto* add_cell_command = dynamic_cast<AddCellCommand*>(command);
        if (add_cell_command != nullptr) {
          buttons_[pl + 2][5]->SetShow(true);
        }
        if (add_ship_command != nullptr) {
          buttons_[pl + 2][6]->SetShow(true);
        }
      }
    }
  }

  window_.SetButtons(buttons_[4]);
  window_.DrawObjects();
  sf::sleep(sf::milliseconds(1000));
  window_.SetButtons(buttons_[5]);
  window_.DrawObjects();

  Player* current_player = players_.data();
  Player* current_rival = &players_[1];
  int current_player_index = 0;
  while (!back_) {
    bool executed = false;
    while (!executed) {
      Command* command = window_.GetCommand();
      auto* cast = dynamic_cast<ShootCommand*>(command);
      if (command->Execute()) {
        if (!window_.isOpen() || !back_) {
          return;
        }
        if (cast != nullptr) {
          break;
        }
      }
      std::cout << "Error. Try again.\n";
    }

    if (current_rival->GetShipCount() == 0) {
      back_ = true;
      std::cout << "Player " << current_player_index + 1 << " won.\n";
      std::cout.flush();
    }
    if (current_player->GetLastShotResult() == ShotResult::Miss) {
      current_rival = &players_[current_player_index];
      current_player_index = 1 - current_player_index;
      current_player = &players_[current_player_index];
    }
  }
}

void GameLoop::Settings() {
  while (window_.isOpen() && !back_) {
    window_.SetButtons(buttons_[1]);
    window_.DrawObjects();
    window_.GetCommand()->Execute();
  }
  back_ = false;
}

void GameLoop::Go() {
  while (window_.isOpen()) {
    window_.GetCommand()->Execute();
  }
}
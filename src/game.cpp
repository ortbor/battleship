#include "../lib/game.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/command.hpp"
#include "../lib/window.hpp"

GameLoop::GameLoop(const Vector2f& size, size_t ships)
    : ships_(ships),
      size_(size),
      players_(std::array<Player, 2>{Player(0, size), Player(1, size)}),
      window(kName) {
  if (!font.loadFromFile(Path().parent_path().string() + kResPrefix)) {
    throw std::runtime_error("Cannot load font");
  }

  Link();
  SetDraw();
  SetCommands();
  SetButtons();
}

GameLoop::~GameLoop() {
  for (auto& item : draw_) {
    delete item;
  }
  for (auto& item : command_) {
    delete item;
  }
  for (auto& scr : buttons_) {
    for (auto& item : scr) {
      delete item;
    }
  }
  draw_.clear();
  command_.clear();
  buttons_.clear();
}

void GameLoop::Link() { players_[0].LinkWithRival(&players_[1]); }

void GameLoop::SetDraw() {
  sf::Text* title = new sf::Text(kName, font, 140);
  title->setFillColor(sf::Color::Red);
  title->setPosition(Vector2f(525, 0));
  title->setStyle(sf::Text::Bold | sf::Text::Underlined);
  draw_.push_back(title);

  std::string player("Player ");
  std::string select(", select\n    your ships!");
  for (size_t i = 0; i < 2; ++i) {
    title = new sf::Text(player + std::to_string(i + 1) + select, font, 80);
    title->setFillColor(sf::Color::Blue);
    title->setPosition(Vector2f(1250, 300));
    draw_.push_back(title);
  }

  sf::RectangleShape* next = new sf::RectangleShape(Vector2f(335, 110));
  next->setFillColor(sf::Color(0, 254, 95));
  next->setPosition(Vector2f(1400, 700));
  draw_.push_back(next);

  title = new sf::Text("Add ship", font, 80);
  title->setFillColor(sf::Color::Red);
  title->setPosition(Vector2f(1410, 700));
  draw_.push_back(title);

  for (size_t pl = 0; pl < 2; ++pl) {
    for (size_t i = 0; i < size_.x; ++i) {
      for (size_t j = 0; j < size_.y; ++j) {
        Vector2f size(65, 65);
        Vector2f left(300 + i * 75, 270 + j * 75);
        sf::RectangleShape* test = new sf::RectangleShape(size);
        test->setFillColor(sf::Color(255, 120, 255));
        test->setPosition(left);
        draw_.push_back(test);
      }
    }
  }

  title = new sf::Text("Game starts in infinity seconds!", font, 120);
  title->setFillColor(sf::Color::Red);
  title->setPosition(Vector2f(150, 450));
  draw_.push_back(title);
}

void GameLoop::SetCommands() {
  command_.push_back(new CloseCommand(&window));
  command_.push_back(new ResizeCommand(&window));
  command_.push_back(new AddShipCommand(players_.data(), &window));
  command_.push_back(new AddShipCommand(players_.data() + 1, &window));

  for (size_t p = 0; p < 2; ++p) {
    for (size_t i = 0; i < size_.x; ++i) {
      for (size_t j = 0; j < size_.y; ++j) {
        auto cell = players_[p].GetField()->GetCell(Vector2f(i, j));
        auto cmd = new AddCellToShipCommand(players_.data() + p, &window, cell);
        command_.push_back(cmd);
      }
    }
  }
}

void GameLoop::SetButtons() {
  buttons_.resize(3);
  for (size_t scr = 0; scr < 3; ++scr) {
    buttons_[scr].push_back(new Button(command_[0], {draw_[0]}));
  }

  for (size_t pl = 0; pl < 2; ++pl) {
    Vector2f left(1400, 700);
    Vector2f right(1735, 910);
    auto coord = std::make_pair(left, right);
    auto* btn = new MouseButton(coord, Mouse::Button::Left, command_[pl + 2],
                                {draw_[3], draw_[4]});
    buttons_[pl].push_back(btn);

    buttons_[pl].push_back(new Button(command_[1], {draw_[pl + 1]}));

    for (size_t i = 0; i < size_.x; ++i) {
      for (size_t j = 0; j < size_.y; ++j) {
        left = Vector2f(300 + i * 75, 270 + j * 75);
        right = Vector2f(365 + i * 75, 335 + j * 75);
        coord = std::make_pair(left, right);
        size_t index = pl * size_.x * size_.y + i * size_.y + j;

        Command* cmd = command_[index + 4];
        btn = new MouseButton(coord, Mouse::Button::Left, cmd,
                              {draw_[index + 5]});
        buttons_[pl].push_back(btn);
      }
    }
  }
  size_t last = 2 * size_.x * size_.y + 5;

  buttons_[2].push_back(new Button(nullptr, {draw_[last]}));
}

void GameLoop::SetAllShips(Player* player) {
  std::cout << "Player " << player->GetIndex() + 1 << ", set your ships.\n";
  for (size_t i = 0; i < ships_; ++i) {
    std::cout << "Insert ship.\n";
    bool ship_set = false;
    stack<AddCellToShipCommand*> command_stack;
    while (!ship_set) {
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
          ship_set = true;
          while (!command_stack.empty()) {
            command_stack.top()->Undo();
            command_stack.pop();
          }
          std::cout << "Added\n";
        }
      } else {
        std::cout << "Error: cannot exec\n";
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

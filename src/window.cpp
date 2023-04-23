#include "../lib/window.hpp"

#include "../lib/button.hpp"
#include "../lib/cell.hpp"
#include "../lib/object.hpp"
#include "../lib/player.hpp"
#include "command.cpp"

GameWindow::GameWindow(array<Player, 2>& players, const Vector2f& size,
                       Vector2f sides)
    : kPath(Path().string()) {
  if (sides.x < 0) {
    sides.x = screen_.x;
    sides.y = screen_.y;
  }
  create(VideoMode(sides.x, sides.y), kName, sf::Style::Fullscreen);
  view_.setSize(sides);
  view_.setCenter(Vector2f(view_.getSize().x / 2, view_.getSize().y / 2));
  setView(view_);

  if (!font_.loadFromFile(kPath + kRes + "symbola.ttf")) {
    throw std::runtime_error("Cannot load font");
  }
  if (!background_.loadFromFile(kPath + kRes + "background.jpg")) {
    throw std::runtime_error("Cannot load background");
  }
  if (!game_theme_.openFromFile(kPath + kRes + "ficha1.what")) {
    throw std::runtime_error("Cannot load ficha");
  }
  if (!main_theme_.openFromFile(kPath + kRes + "ficha2.what")) {
    throw std::runtime_error("Cannot load ficha");
  }

  main_theme_.setLoop(true);
  main_theme_.play();

  Configure(players, size);
  DrawObjects();
}

GameWindow::~GameWindow() {}

const std::unique_ptr<Command>& GameWindow::GetCommand() {
  while (true) {
    waitEvent(event_);
    for (auto& button : buttons_[button_str_]) {
      if (button.second->IsPressed(event_)) {
        return button.second->GetCommand();
      }
    }
  }
}

unordered_map<string, map<string, Button*>>& GameWindow::GetButtons() {
  return buttons_;
}

void GameWindow::SetButtons(const string& str) {
  button_str_ = str;
  DrawObjects();
}

void GameWindow::SetShow(const string& scene, const string& elem, bool show) {
  buttons_[scene][elem]->SetShow(show);
}

void GameWindow::DrawObjects() {
  clear();
  for (const auto& item : buttons_[button_str_]) {
    if (item.second->GetShow()) {
      for (const auto& object : item.second->GetDrawable()) {
        draw(*object.sprite);
      }
    }
  }
  display();
}

void GameWindow::SetVolume(Volume value) {
  switch (value) {
    case Volume::Silence:
      main_theme_.setVolume(0);
      game_theme_.setVolume(0);
      main_theme_.pause();
      game_theme_.pause();
      break;

    case Volume::Less:
      main_theme_.setVolume(std::max(0.F, main_theme_.getVolume() - 10));
      game_theme_.setVolume(std::max(0.F, main_theme_.getVolume() - 10));
      break;

    case Volume::More:
      main_theme_.setVolume(std::min(100.F, main_theme_.getVolume() + 10));
      game_theme_.setVolume(std::min(100.F, main_theme_.getVolume() + 10));
      if (main_theme_.getStatus() == sf::SoundSource::Paused) {
        main_theme_.play();
      }
      if (game_theme_.getStatus() == sf::SoundSource::Paused) {
        game_theme_.play();
      }
      break;

    case Volume::Max:
      main_theme_.setVolume(100);
      game_theme_.setVolume(100);
      if (main_theme_.getStatus() == sf::SoundSource::Paused) {
        main_theme_.play();
      }
      if (game_theme_.getStatus() == sf::SoundSource::Paused) {
        game_theme_.play();
      }
      break;

    default:
      throw std::runtime_error("Unknown volume!");
      break;
  }
}

std::filesystem::path GameWindow::Path() {
  std::string path_str(PATH_MAX + 1, 0);
#if defined(__unix)
  if (readlink("/proc/self/exe", path_str.data(), PATH_MAX) == -1) {
    throw std::runtime_error("Cannot specify program path!");
  }
#elif defined(_WIN32)
  GetModuleFileName(NULL, path_str.data(), PATH_MAX);
#else
  throw std::runtime_error("Unsupported OS");
#endif
  return std::filesystem::path(path_str).parent_path().parent_path();
}

void GameWindow::Configure(array<Player, 2>& players, const Vector2f& size) {
  buttons_["menu"]["settings"] = std::make_unique<MouseButton>(
      Mouse::Button::Left, std::make_unique<SetCommand>("settings"),
      RectObject({530, 150}, {0, 255, 95}, {700, 820}),
      TextObject("Settings", 140, Color::Red, {720, 790}, font_));

  buttons_["menu"]["play"] =  std::make_unique<MouseButton>(
      Mouse::Button::Left, std::make_unique<SetCommand>("ip"),
      RectObject({340, 150}, {0, 255, 95}, {790, 300}),
       TextObject("Play", 140, Color::Red, {820, 270}, font_));

  buttons_["menu"]["return"] = std::make_unique<MouseButton>(
      Mouse::Button::Left,
      std::make_unique<ExecCommand>(*this, Event::MouseButtonPressed,
                                    [](GameWindow& window) { window.close(); }),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("X", 60, Color::Red, {97, 75}, font_));

  buttons_["play"]["return"] = std::make_unique<MouseButton>(
      Mouse::Button::Left, std::make_unique<SetCommand>("menu"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 70}, font_));

  buttons_["settings"]["return"] = std::make_unique<MouseButton>(
      Mouse::Button::Left, std::make_unique<SetCommand>("menu"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 70}, font_));

  buttons_["settings"]["volume"] = std::make_unique<Button>(
      nullptr,
      TextObject("Volume", 120, Color::Red, {430, 490}, font_, Text::Bold));

  buttons_["settings"]["vol_silence"] = std::make_unique<MouseButton>(
      Mouse::Button::Left,
      std::make_unique<ExecCommand>(
          *this, Event::MouseButtonPressed,
          [](GameWindow& window) { window.SetVolume(Volume::Silence); }),
      RectObject({100, 100}, {0, 255, 95}, {900, 530}),
      TextObject("<X", 60, Color::Red, {902, 540}, font_));

  buttons_["settings"]["vol_less"] = std::make_unique<MouseButton>(
      Mouse::Button::Left,
      std::make_unique<ExecCommand>(
          *this, Event::MouseButtonPressed,
          [](GameWindow& window) { window.SetVolume(Volume::Less); }),
      RectObject({100, 100}, {0, 255, 95}, {1050, 530}),
      TextObject("-", 60, Color::Red, {1090, 535}, font_));

  buttons_["settings"]["vol_more"] = std::make_unique<MouseButton>(
      Mouse::Button::Left,
      std::make_unique<ExecCommand>(
          *this, Event::MouseButtonPressed,
          [](GameWindow& window) { window.SetVolume(Volume::More); }),
      RectObject({100, 100}, {0, 255, 95}, {1200, 530}),
      TextObject("+", 60, Color::Red, {1228, 535}, font_));

  buttons_["settings"]["vol_max"] = std::make_unique<MouseButton>(
      Mouse::Button::Left,
      std::make_unique<ExecCommand>(
          *this, Event::MouseButtonPressed,
          [](GameWindow& window) { window.SetVolume(Volume::Max); }),
      RectObject({100, 100}, {0, 255, 95}, {1350, 530}),
      TextObject("<))", 60, Color::Red, {1355, 535}, font_));

  for (auto& item : buttons_) {
    item.second["close"] =
        std::make_unique<Button>(std::make_unique<ExecCommand>(
            *this, Event::Closed, [](GameWindow& window) { window.close(); }));

    item.second["resize"] =
        std::make_unique<Button>(std::make_unique<ExecCommand>(
            *this, Event::Resized,
            [](GameWindow& window) { window.DrawObjects(); }));

    item.second["background"] = std::make_unique<Button>(
        nullptr, DrawObject(std::make_unique<Sprite>(background_)),
        TextObject(kName, 140, Color::Red, {475, 0}, font_,
                   Text::Bold | Text::Underlined));
  }
}

// void GameWindow::Configure(array<Player, 2> & players, const Vector2f& size)
// {
/*
  for (size_t pl = 0; pl < 2; ++pl) {
    buttons_["select_" + std::to_string(pl)]["text"] = new Button(
        nullptr, {GetText("Player " + std::to_string(pl + 1) +
                              ", select\n    your ships!",
                          80, Color::Blue, Vector2f(1110 - pl * 850,
  300))});

    buttons_["select_" + std::to_string(pl)]["ship"] = new MouseButton(
        Mouse::Button::Left, new AddShipCommand(players.data() + pl),
        {GetShape(Vector2f(335, 110), Color(0, 255, 95),
                  Vector2f(1210 - pl * 850, 530)),
         GetText("Add ship", 80, Color::Red, Vector2f(1220 - pl * 850,
  530))});

    buttons_["select_" + std::to_string(pl)]["return"] = new MouseButton(
        Mouse::Button::Left, new SetButtonsCommand("menu"),
        {GetShape(Vector2f(100, 100), Color(0, 255, 95), Vector2f(70, 65)),
         GetText("<-", 60, Color::Red, {85, 72})});

    buttons_["select_" + std::to_string(pl)]["ok"] =
        new Button(nullptr,
                   {GetText("Success!", 80, Color::Green,
                            Vector2f(1240 - pl * 850, 750), Text::Bold)},
                   false);

    buttons_["select_" + std::to_string(pl)]["errcell"] =
        new Button(nullptr,
                   {GetText("Cannot select\n    this cell!", 80, Color::Red,
                            Vector2f(1120 - pl * 850, 750), Text::Bold)},
                   false);

    buttons_["select_" + std::to_string(pl)]["errship"] =
        new Button(nullptr,
                   {GetText("Wrong shaped ship!", 80, Color::Red,
                            Vector2f(1030 - pl * 850, 750), Text::Bold)},
                   false);

    buttons_["play_" + std::to_string(pl)]["turn"] = new Button(
        nullptr, {GetText("Player " + std::to_string(pl + 1) + " turn ",
  100, Color::Red, {675, 930}, sf::Text::Bold)});

    buttons_["play_" + std::to_string(pl)]["field_my"] = new Button(
        nullptr,
        {GetText("My field", 80, Color::Red, Vector2f(133 + pl * 1200,
  950))});

    buttons_["play_" + std::to_string(pl)]["field_rival"] =
        new Button(nullptr, {GetText("Rival field", 80, Color::Red,
                                     Vector2f(1410 - pl * 1200, 950))});

    buttons_["play_" + std::to_string(pl)]["return"] = new MouseButton(
        Mouse::Left, new SetButtonsCommand("menu"),
        {GetShape(Vector2f(100, 100), Color(0, 255, 95), Vector2f(70, 65)),
         GetText("<-", 60, Color::Red, {85, 72})});

    buttons_["turn_" + std::to_string(pl)]["text"] = new Button(
        nullptr,
        {GetText("Player " + std::to_string(pl + 1) + ", FIGHT!\n", 120,
                 Color::Red, {530, 450}, Text::Bold | Text::Underlined)});

    buttons_["won_" + std::to_string(pl)]["text"] = new Button(
        nullptr, {GetText("Player " + std::to_string(pl + 1) + " won!\n",
  120, Color::Red, {600, 350}, Text::Bold), GetText("        Do you feel
  proud of yourself after\n" "you killed all innocent other player's
  ships?..", 60, Color::Red, {360, 750}, Text::Bold)});

    buttons_["won_" + std::to_string(pl)]["return"] = new MouseButton(
        Mouse::Button::Left, new SetButtonsCommand("menu"),
        {GetShape(Vector2f(100, 100), Color(0, 255, 95), Vector2f(70, 65)),
         GetText("<-", 60, Color::Red, {85, 70})});

    for (size_t i = 0; i < size.x; ++i) {
      for (size_t j = 0; j < size.y; ++j) {
        auto pos_my = Vector2f(140 + i * 70 + pl * 940, 250 + j * 70);
        auto pos_rv = Vector2f(1080 + i * 70 - pl * 940, 250 + j * 70);
        std::string ind = std::to_string(i * size.y + j);
        auto* cell_my = players[pl].GetField()->GetCell(Vector2f(i, j));
        auto* cell_rv = players[pl].GetRField()->GetCell(Vector2f(i, j));

        cell_my->SetShape(
            GetShape(Vector2f(65, 65), Color(255, 120, 255), pos_my));

        cell_rv->SetShape(
            GetShape(Vector2f(65, 65), Color(255, 255, 255), pos_rv));

        buttons_["select_" + std::to_string(pl)]["cell" + ind] =
            new MouseButton(Mouse::Button::Left,
                            new AddCellCommand(players.data() + pl,
  cell_my), {cell_my->GetShape()});

        buttons_["play_" + std::to_string(pl)]["cell_my" + ind] =
            new Button(nullptr, {cell_my->GetShape()});

        buttons_["play_" + std::to_string(pl)]["cell_rival" + ind] =
            new MouseButton(Mouse::Button::Left,
                            new ShootCommand(players.data() + pl, cell_rv),
                            {cell_rv->GetShape()});
      }
    }
  }

  buttons_["ip"]["0"] = new KeyboardButton(Keyboard::Key::Num0, new AddSymbolCommand('0'), {});
  buttons_["ip"]["1"] = new KeyboardButton(Keyboard::Key::Num1, new AddSymbolCommand('1'), {});
  buttons_["ip"]["2"] = new KeyboardButton(Keyboard::Key::Num2, new AddSymbolCommand('2'), {});
  buttons_["ip"]["3"] = new KeyboardButton(Keyboard::Key::Num3, new AddSymbolCommand('3'), {});
  buttons_["ip"]["4"] = new KeyboardButton(Keyboard::Key::Num4, new AddSymbolCommand('4'), {});
  buttons_["ip"]["5"] = new KeyboardButton(Keyboard::Key::Num5, new AddSymbolCommand('5'), {});
  buttons_["ip"]["6"] = new KeyboardButton(Keyboard::Key::Num6, new AddSymbolCommand('6'), {});
  buttons_["ip"]["7"] = new KeyboardButton(Keyboard::Key::Num7, new AddSymbolCommand('7'), {});
  buttons_["ip"]["8"] = new KeyboardButton(Keyboard::Key::Num8, new AddSymbolCommand('8'), {});
  buttons_["ip"]["9"] = new KeyboardButton(Keyboard::Key::Num9, new AddSymbolCommand('9'), {});
  buttons_["ip"]["."] = new KeyboardButton(Keyboard::Key::Period, new AddSymbolCommand('.'), {});
  buttons_["ip"]["enter"] = new KeyboardButton(Keyboard::Key::Enter, new SetButtonsCommand("select_0"), {});

  buttons_["shift_select"]["text"] =
      new Button(nullptr, {GetText("Player 2, be ready to select\n"
                                   "        ships in 2 seconds!\n"
                                   " Player 1, DO NOT LOOK!",
                                   120, Color::Cyan, {250, 350},
  Text::Bold)});

  buttons_["starts"]["text"] = new Button(
      nullptr,
      {GetText("Game starts in 2 seconds!", 120, Color::Red, {300, 450})});

  buttons_["won"]["first"] = new Button(
      nullptr,
      {GetText("Player 1 won", 120, Color::Red, {420, 350}, Text::Bold)});*/

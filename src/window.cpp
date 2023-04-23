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
  if (!game_theme_.openFromFile(kPath + kRes + "ficha3.whaaaat")) {
    throw std::runtime_error("Cannot load ficha");
  }
  if (!main_theme_.openFromFile(kPath + kRes + "ficha2.what")) {
    throw std::runtime_error("Cannot load fichaaaa");
  }

  main_theme_.setLoop(true);
  main_theme_.play();

  Configure(players, size);
  DrawObjects();
}

GameWindow::~GameWindow() {}

const std::shared_ptr<Command>& GameWindow::GetCommand() {
  while (true) {
    waitEvent(event_);
    for (auto& button : buttons_[button_str_]) {
      if (button.second->IsPressed(event_)) {
        return button.second->GetCommand();
      }
    }
  }
}

unordered_map<string, map<string, std::shared_ptr<Button>>>&
GameWindow::GetButtons() {
  return buttons_;
}

Event& GameWindow::GetEvent() { return event_; }

void GameWindow::SetButtons(const string& str) {
  button_str_ = str;
  DrawObjects();
}

void GameWindow::SetShow(const string& scene, const string& elem, size_t index, bool show) {
  buttons_[scene][elem].get()->GetDrawable()[index].show = show;
}

void GameWindow::DrawObjects() {
  clear();
  for (const auto& item : buttons_[button_str_]) {
    for (const auto& object : item.second->GetDrawable()) {
      if (object.show) {
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
      if (main_theme_.getVolume() == 0) {
        main_theme_.pause();
        game_theme_.pause();
      }
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
  buttons_["menu"]["play"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("play"),
      RectObject({340, 150}, {0, 255, 95}, {790, 300}),
      TextObject("Play", 140, Color::Red, {820, 270}, font_));

  buttons_["menu"]["settings"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("settings"),
      RectObject({530, 150}, {0, 255, 95}, {700, 820}),
      TextObject("Settings", 140, Color::Red, {720, 790}, font_));

  buttons_["menu"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left,
      std::make_shared<ExecCommand>(*this, Event::MouseButtonPressed,
                                    [](GameWindow& window) { window.close(); }),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("X", 60, Color::Red, {97, 75}, font_));

  buttons_["settings"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("menu"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 70}, font_));

  buttons_["settings"]["volume"] = std::make_shared<Button>(
      nullptr,
      TextObject("Volume", 120, Color::Red, {430, 490}, font_, Text::Bold));

  buttons_["settings"]["vol_silence"] = std::make_shared<MouseButton>(
      Mouse::Button::Left,
      std::make_shared<ExecCommand>(
          *this, Event::MouseButtonPressed,
          [](GameWindow& window) { window.SetVolume(Volume::Silence); }),
      RectObject({100, 100}, {0, 255, 95}, {900, 530}),
      TextObject("<X", 60, Color::Red, {902, 540}, font_));

  buttons_["settings"]["vol_less"] = std::make_shared<MouseButton>(
      Mouse::Button::Left,
      std::make_shared<ExecCommand>(
          *this, Event::MouseButtonPressed,
          [](GameWindow& window) { window.SetVolume(Volume::Less); }),
      RectObject({100, 100}, {0, 255, 95}, {1050, 530}),
      TextObject("-", 60, Color::Red, {1090, 535}, font_));

  buttons_["settings"]["vol_more"] = std::make_shared<MouseButton>(
      Mouse::Button::Left,
      std::make_shared<ExecCommand>(
          *this, Event::MouseButtonPressed,
          [](GameWindow& window) { window.SetVolume(Volume::More); }),
      RectObject({100, 100}, {0, 255, 95}, {1200, 530}),
      TextObject("+", 60, Color::Red, {1228, 535}, font_));

  buttons_["settings"]["vol_max"] = std::make_shared<MouseButton>(
      Mouse::Button::Left,
      std::make_shared<ExecCommand>(
          *this, Event::MouseButtonPressed,
          [](GameWindow& window) { window.SetVolume(Volume::Max); }),
      RectObject({100, 100}, {0, 255, 95}, {1350, 530}),
      TextObject("<))", 60, Color::Red, {1355, 535}, font_));

  buttons_["play"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("menu"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 70}, font_));

  buttons_["play"]["connect"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("ip"),
      RectObject({665, 150}, {0, 255, 95}, {630, 300}),
      TextObject("Throw a glove", 100, Color::Red, {640, 300}, font_));

  buttons_["play"]["wait"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("connect"),
      RectObject({1210, 150}, {0, 255, 95}, {360, 820}),
      TextObject("Wait for a dick to your ass", 100, Color::Red, {370, 820},
                 font_));

  buttons_["ip"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("play"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 70}, font_));

  buttons_["ip"]["number"] =
      std::make_shared<KeyboardButton>(std::make_shared<AddSymbolCommand>());

  buttons_["ip"]["save"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("select_0"),
      RectObject({340, 150}, {0, 255, 95}, {790, 300}),
      TextObject("Save", 140, Color::Red, {820, 270}, font_));

  buttons_["connect"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("play"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 70}, font_));

  buttons_["select_0"]["text"] = std::make_shared<Button>(
      nullptr,
      TextObject("Select your ships", 80, Color::Blue, {1110, 300}, font_));

  buttons_["select_0"]["ship"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<AddShipCommand>(players.data()),
      RectObject({335, 110}, {0, 255, 95}, {1210, 530}),
      TextObject("Add ship", 80, Color::Red, {1220, 530}, font_));

  buttons_["select_0"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("play"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 72}, font_));

  buttons_["select_0"]["status"] = std::make_shared<Button>(
      nullptr,
      TextObject("Success!", 80, Color::Green, {1240, 750}, font_, Text::Bold,
                 false),
      TextObject("Cannot select\n    this cell!", 80, Color::Red, {1120, 750},
                 font_, Text::Bold, false),
      TextObject("Wrong shaped ship!", 80, Color::Red, {1030, 750}, font_,
                 Text::Bold, false));

  buttons_["play_0"]["return"] = std::make_shared<MouseButton>(
      Mouse::Left, std::make_shared<SetCommand>("play"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 72}, font_));

  buttons_["play_0"]["turn"] = std::make_shared<Button>(
      nullptr, TextObject("Your turn ", 100, Color::Red, {675, 930}, font_,
                          sf::Text::Bold));

  buttons_["play_0"]["field_your"] = std::make_shared<Button>(
      nullptr, TextObject("Your field", 80, Color::Red, {133, 950}, font_));

  buttons_["play_0"]["field_rival"] = std::make_shared<Button>(
      nullptr, TextObject("Rival field", 80, Color::Red, {1410, 950}, font_));

  buttons_["won_0"]["text"] = std::make_shared<Button>(
      nullptr,
      TextObject("You win!", 120, Color::Red, {600, 350}, font_, Text::Bold),
      TextObject("        Do you feel proud of yourself after\n"
                 "you killed all innocent other player's ships?..",
                 60, Color::Red, {360, 750}, font_, Text::Bold));

  buttons_["won_0"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("menu"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 70}, font_));

  buttons_["won_1"]["text"] = std::make_shared<Button>(
      nullptr,
      TextObject("Rival win!", 120, Color::Red, {600, 350}, font_, Text::Bold),
      TextObject("Don't worry, be happy!", 60, Color::Red, {360, 750}, font_,
                 Text::Bold));

  buttons_["won_1"]["return"] = std::make_shared<MouseButton>(
      Mouse::Button::Left, std::make_shared<SetCommand>("menu"),
      RectObject({100, 100}, {0, 255, 95}, {70, 65}),
      TextObject("<-", 60, Color::Red, {85, 70}, font_));

  for (size_t pl = 0; pl < 2; ++pl) {
    for (size_t i = 0; i < size.x; ++i) {
      for (size_t j = 0; j < size.y; ++j) {
        auto pos_my = Vector2f(140 + i * 70, 250 + j * 70);
        auto pos_rv = Vector2f(1080 + i * 70 - pl * 940, 250 + j * 70);
        std::string ind = std::to_string(i * size.y + j);
        auto* cell_my = players[pl].GetField()->GetCell(Vector2f(i, j));
        auto* cell_rv = players[pl].GetRField()->GetCell(Vector2f(i, j));

        buttons_["select_" + std::to_string(pl)]["cell" + ind] =
            std::make_shared<MouseButton>(
                Mouse::Button::Left,
                std::make_shared<AddCellCommand>(players.data() + pl, cell_my),
                RectObject({65, 65}, {255, 120, 255}, pos_my));

        buttons_["play_" + std::to_string(pl)]["cell_my" + ind] =
            std::make_shared<Button>(
                nullptr, buttons_["select_" + std::to_string(pl)]["cell" + ind]
                             .get()
                             ->GetDrawable()[0]);

        buttons_["play_" + std::to_string(pl)]["cell_rival" + ind] =
            std::make_shared<MouseButton>(
                Mouse::Button::Left,
                std::make_shared<ShootCommand>(players.data() + pl, cell_rv),
                RectObject({65, 65}, {255, 255, 255}, pos_rv));

        cell_my->SetShape(dynamic_cast<RectangleShape*>(
            buttons_["select_" + std::to_string(pl)]["cell" + ind]
                .get()
                ->GetDrawable()[0]
                .sprite.get()));

        cell_rv->SetShape(dynamic_cast<RectangleShape*>(
            buttons_["play_" + std::to_string(pl)]["cell_rival" + ind]
                .get()
                ->GetDrawable()[0]
                .sprite.get()));
      }
    }
  }

  for (auto& item : buttons_) {
    item.second["close"] =
        std::make_shared<Button>(std::make_shared<ExecCommand>(
            *this, Event::Closed, [](GameWindow& window) { window.close(); }));

    item.second["resize"] =
        std::make_shared<Button>(std::make_shared<ExecCommand>(
            *this, Event::Resized,
            [](GameWindow& window) { window.DrawObjects(); }));

    item.second["background"] = std::make_shared<Button>(
        nullptr, DrawObject(std::make_shared<Sprite>(background_)),
        TextObject(kName, 140, Color::Red, {475, 0}, font_,
                   Text::Bold | Text::Underlined));
  }
}

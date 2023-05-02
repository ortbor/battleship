#include "../lib/window.hpp"

#include "../lib/button.hpp"
#include "../lib/object.hpp"

<<<<<<< HEAD
GameWindow::GameWindow(array<Player, 2>& players, const Vector2f& size,
                       Vector2f sides)
    : kPath(Path().string()) {
  if (sides.x < 0) {
    sides.x = 1920;
    sides.y = 1080;
  }
  create(VideoMode(sides.x, sides.y), kName, sf::Style::Fullscreen);
  view_.setSize(sides);
  view_.setCenter(Vector2f(view_.getSize().x / 2, view_.getSize().y / 2));
  setView(view_);
||||||| 58d15e7
GameWindow::GameWindow(array<Player, 2>& players, const Vector2f& size,
                       Vector2f sides) {
  if (sides.x < 0) {
    sides.x = screen_.x;
    sides.y = screen_.y;
  }
  create(VideoMode(sides.x, sides.y), kName, sf::Style::Fullscreen);
  view_.setSize(sides);
  view_.setCenter(Vector2f(view_.getSize().x / 2, view_.getSize().y / 2));
  setView(view_);
=======
GameWindow::GameWindow(array<Player, 2>& players, const Vector2u& size) {
  create(VideoMode(1920, 1080), kName, sf::Style::Fullscreen);
  m_view.setSize(Vector2f(getSize()));
  m_view.setCenter(Vector2f(m_view.getSize().x / 2, m_view.getSize().y / 2));
  setView(m_view);
>>>>>>> dev-ntheme

<<<<<<< HEAD
  if (!font_.loadFromFile(kPath + kRes + "symbola.ttf")) {
    throw std::runtime_error("Cannot load font");
||||||| 58d15e7
  if (!font_.loadFromFile(Path().string() + kRes + "symbola.ttf")) {
    throw std::runtime_error("Cannot load font");
=======
  if (!m_music["game"].openFromFile(bs::Path() + kRes + "ficha2.what")) {
    throw std::runtime_error("Cannot load ficha");
>>>>>>> dev-ntheme
  }
<<<<<<< HEAD
  if (!background_.loadFromFile(kPath + kRes + "background.jpg")) {
    throw std::runtime_error("Cannot load background");
||||||| 58d15e7
  if (!background_.loadFromFile(Path().string() + kRes + "background.jpg")) {
    throw std::runtime_error("Cannot load background");
=======
  if (!m_music["main"].openFromFile(bs::Path() + kRes + "ficha1.what")) {
    throw std::runtime_error("Cannot load fichaaaa");
  }
  if (!m_movie.openFromFile(bs::Path() + kRes + "ficha3.what")) {
    throw std::runtime_error("Cannot load ficha");
>>>>>>> dev-ntheme
  }
  if (!movie_.openFromFile(kPath + kRes + "bug.or.ficha")) {
    throw std::runtime_error("Cannot load ficha");
  }

  if (!music_["game"].openFromFile(kPath + kRes + "ficha3.whaaaat")) {
    throw std::runtime_error("Cannot load ficha");
  }
  if (!music_["main"].openFromFile(kPath + kRes + "ficha2.what")) {
    throw std::runtime_error("Cannot load fichaaaa");
  }

  music_["main"].setLoop(true);
  music_["game"].setLoop(true);
  music_["main"].play();
  movie_.fit(0, 0, sides.x, sides.y);

  m_music["game"].setLoop(true);
  m_music["main"].setLoop(true);
  m_music["main"].play();
  m_movie.fit(0, 0, getSize().x, getSize().y);

  m_boxes["scene"] = "menu";
  m_boxes["port"] = "2000";
  m_boxes["ip"] = "";

  m_push.Config(players, size, m_music, m_boxes);
  DrawObjects();
}

<<<<<<< HEAD
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
||||||| 58d15e7
GameWindow::~GameWindow() {
  for (auto& scr : buttons_) {
    for (auto& item : scr.second) {
      delete item.second->GetCommand();
    }
    if (scr.first != "select_0" && scr.first != "select_1") {
      for (auto& item : scr.second) {
        for (auto& draw : item.second->GetDrawable()) {
          delete draw;
        }
      }
    }
  }
=======
GameWindow::~GameWindow() {}

const std::shared_ptr<Command>& GameWindow::GetCommand() {
  while (true) {
    waitEvent(m_event);
    auto* btn = m_push.GetPressed(m_boxes["scene"], m_event);
    if (btn != nullptr) {
      return btn->GetCommand();
    }
  } 
>>>>>>> dev-ntheme
}

<<<<<<< HEAD
unordered_map<string, map<string, std::shared_ptr<Button>>>&
GameWindow::GetButtons() {
  return buttons_;
}

Event& GameWindow::GetEvent() { return event_; }

Music& GameWindow::GetMusic(const string& elem) { return music_[elem]; }

string& GameWindow::GetBox() { return text_box_; }

void GameWindow::SetObject(const string& scene, const string& elem,
                           size_t index, const string& str) {
  dynamic_cast<Text*>(
      buttons_[scene][elem].get()->GetDrawable()[index].sprite.get())
      ->setString(str);
  DrawObjects();
}
||||||| 58d15e7
Command* GameWindow::GetCommand() {
  while (true) {
    waitEvent(event_);
    for (auto& button : buttons_[button_str_]) {
      if (button.second->IsPressed(event_, *this)) {
        return button.second->GetCommand();
      }
    }
  }
}
=======
Push& GameWindow::GetButtons() { return m_push; }

Event& GameWindow::GetEvent() { return m_event; }

Music& GameWindow::GetMusic(const string& elem) { return m_music[elem]; }

map<string, string>& GameWindow::GetBoxes() { return m_boxes; }
>>>>>>> dev-ntheme

void GameWindow::SetButtons(const string& str) {
  m_boxes["scene"] = str;
  DrawObjects();
}

<<<<<<< HEAD
void GameWindow::SetShow(const string& scene, const string& elem, size_t index,
                         bool show) {
  buttons_[scene][elem].get()->GetDrawable()[index].show = show;
  DrawObjects();
||||||| 58d15e7
void GameWindow::SetShow(const string& scene, const string& elem, bool show) {
  buttons_[scene][elem]->SetShow(show);
=======
void GameWindow::SetObject(const string& scene, const string& elem,
                           size_t index, const string& str) {
  dynamic_cast<Text*>(m_push.Get(scene, elem)->GetShapes()[index].sprite.get())
      ->setString(str);
  DrawObjects();
}

void GameWindow::SetShow(const string& scene, const string& elem, bool show,
                         int index) {
  if (index == -1) {
    for (auto& item : m_push.Get(scene, elem)->GetShapes()) {
      item.show = show;
    }
  } else {
  m_push.Get(scene, elem)->GetShapes()[index].show = show;
  }
  DrawObjects();
>>>>>>> dev-ntheme
}

void GameWindow::DrawObjects() {
  clear();
<<<<<<< HEAD
  for (const auto& item : buttons_[button_str_]) {
    for (const auto& object : item.second->GetDrawable()) {
      if (object.show) {
        draw(*object.sprite);
||||||| 58d15e7
  for (const auto& item : buttons_[button_str_]) {
    if (item.second->GetShow()) {
      for (const auto& object : item.second->GetDrawable()) {
        draw(*object);
=======
  for (const auto& item : m_push.Data(m_boxes["scene"])) {
    for (const auto& object : item.second->GetShapes()) {
      if (object.show) {
        draw(*object.sprite);
>>>>>>> dev-ntheme
      }
    }
  }
  display();
}

<<<<<<< HEAD
void GameWindow::SetVolume(Volume value) {
  for (auto& elem : music_) {
    switch (value) {
      case Volume::Silence:
        elem.second.setVolume(0);
        elem.second.pause();
        break;

      case Volume::Less:
        elem.second.setVolume(std::max(0.F, elem.second.getVolume() - 10));
        if (elem.second.getVolume() == 0) {
          elem.second.pause();
        }
        break;

      case Volume::More:
        elem.second.setVolume(std::min(100.F, elem.second.getVolume() + 10));
        if (elem.second.getStatus() == sf::SoundSource::Paused) {
          elem.second.play();
        }
        break;

      case Volume::Max:
        elem.second.setVolume(100);
        if (elem.second.getStatus() == sf::SoundSource::Paused) {
          elem.second.play();
        }
        break;

      default:
        throw std::runtime_error("Unknown volume!");
        break;
    }
  }
}

void GameWindow::Ficha() {
  music_["main"].stop();
  music_["game"].stop();
  movie_.play();
  while (true) {
    movie_.update();
    clear();
    draw(movie_);
    display();
  }
}

std::filesystem::path GameWindow::Path() {
  std::string path_str(PATH_MAX + 1, 0);
#if defined(__unix)
  if (readlink("/proc/self/exe", path_str.data(), PATH_MAX) == -1) {
    throw std::runtime_error("Cannot specify program path!");
  }
#elif defined(_WIN32)
  GetModuleFileName(NULL, path_str.data(), 0 PATH_MAX);
#else
  throw std::runtime_error("Unsupported OS");
#endif
  return std::filesystem::path(path_str).parent_path().parent_path();
}
||||||| 58d15e7
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

Text* GameWindow::GetText(const string& str, size_t size, const Color& color,
                          const Vector2f& pos, int style) {
  Text* title = new Text(str, font_, size);
  title->setFillColor(color);
  title->setPosition(pos);
  title->setStyle(style);
  return title;
}

RectangleShape* GameWindow::GetShape(const Vector2f& size, const Color& color,
                                     const Vector2f& pos) {
  sf::RectangleShape* box = new sf::RectangleShape(size);
  box->setFillColor(color);
  box->setPosition(pos);
  return box;
}

void GameWindow::Configure(array<Player, 2>& players, const Vector2f& size) {
  buttons_["menu"]["play"] = new MouseButton(
      Mouse::Button::Left, new SetButtonsCommand("select_0"),
      {GetShape(Vector2f(340, 150), Color(0, 255, 95), Vector2f(790, 300)),
       GetText("Play", 140, Color::Red, {820, 270})});

  buttons_["menu"]["settings"] = new MouseButton(
      Mouse::Button::Left, new SetButtonsCommand("settings"),
      {GetShape(Vector2f(530, 150), Color(0, 255, 95), Vector2f(700, 820)),
       GetText("Settings", 140, Color::Red, {720, 790})});

  buttons_["menu"]["return"] = new MouseButton(
      Mouse::Button::Left,
      new ExecCommand<GameWindow>(this, Event::Closed,
                                  [](GameWindow* window) { window->close(); }),
      {GetShape(Vector2f(100, 100), Color(0, 255, 95), Vector2f(70, 65)),
       GetText("X", 60, Color::Red, {97, 75})});

  buttons_["settings"]["return"] = new MouseButton(
      Mouse::Button::Left, new SetButtonsCommand("menu"),
      {GetShape(Vector2f(100, 100), Color(0, 255, 95), Vector2f(70, 65)),
       GetText("<-", 60, Color::Red, {85, 70}),
       GetText("Nothing yet!", 140, Color::Red, {570, 530})});

  for (size_t pl = 0; pl < 2; ++pl) {
    buttons_["select_" + std::to_string(pl)]["text"] = new Button(
        nullptr, {GetText("Player " + std::to_string(pl + 1) +
                              ", select\n    your ships!",
                          80, Color::Blue, Vector2f(1110 - pl * 850, 300))});

    buttons_["select_" + std::to_string(pl)]["ship"] = new MouseButton(
        Mouse::Button::Left, new AddShipCommand(players.data() + pl),
        {GetShape(Vector2f(335, 110), Color(0, 255, 95),
                  Vector2f(1210 - pl * 850, 550)),
         GetText("Add ship", 80, Color::Red, Vector2f(1220 - pl * 850, 550))});

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
        nullptr, {GetText("Player " + std::to_string(pl + 1) + " turn ", 100,
                          Color::Red, {675, 930}, sf::Text::Bold)});

    buttons_["play_" + std::to_string(pl)]["field_my"] = new Button(
        nullptr,
        {GetText("My field", 80, Color::Red, Vector2f(133 + pl * 1200, 950))});

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
        nullptr, {GetText("Player " + std::to_string(pl + 1) + " won!\n", 120,
                          Color::Red, {600, 350}, Text::Bold),
                  GetText("        Do you feel proud of yourself after\n"
                          "you killed all innocent other player's ships?..",
                          60, Color::Red, {360, 750}, Text::Bold)});

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
                            new AddCellCommand(players.data() + pl, cell_my),
                            {cell_my->GetShape()});

        buttons_["play_" + std::to_string(pl)]["cell_my" + ind] =
            new Button(nullptr, {cell_my->GetShape()});

        buttons_["play_" + std::to_string(pl)]["cell_rival" + ind] =
            new MouseButton(Mouse::Button::Left,
                            new ShootCommand(players.data() + pl, cell_rv),
                            {cell_rv->GetShape()});
      }
    }
  }

  buttons_["shift_select"]["text"] =
      new Button(nullptr, {GetText("Player 2, be ready to select\n"
                                   "        ships in 2 seconds!\n"
                                   " Player 1, DO NOT LOOK!",
                                   120, Color::Cyan, {250, 350}, Text::Bold)});

  buttons_["starts"]["text"] = new Button(
      nullptr,
      {GetText("Game starts in 2 seconds!", 120, Color::Red, {300, 450})});

  buttons_["won"]["first"] = new Button(
      nullptr,
      {GetText("Player 1 won", 120, Color::Red, {420, 350}, Text::Bold)});

  for (auto& item : buttons_) {
    item.second["close"] = new Button(new ExecCommand<GameWindow>(
        this, Event::Closed, [](GameWindow* window) { window->close(); }));

    item.second["resize"] = new Button(new ExecCommand<GameWindow>(
        this, Event::Resized,
        [](GameWindow* window) { window->DrawObjects(); }));

    item.second["background"] = new Button(
        nullptr,
        {new sf::Sprite(background_), GetText(kName, 140, Color::Red, {475, 0},
                                              Text::Bold | Text::Underlined)});
  }
}
=======
void GameWindow::SetVolume(CMDVolume type) {
  for (auto& elem : m_music) {
    switch (type) {
      case CMDVolume::Silence:
        elem.second.setVolume(0);
        elem.second.pause();
        break;

      case CMDVolume::Less:
        elem.second.setVolume(std::max(0.F, elem.second.getVolume() - 10));
        if (elem.second.getVolume() == 0) {
          elem.second.pause();
        }
        break;

      case CMDVolume::More:
        elem.second.setVolume(std::min(100.F, elem.second.getVolume() + 10));
        if (elem.second.getStatus() == sf::SoundSource::Paused) {
          elem.second.play();
        }
        break;

      case CMDVolume::Max:
        elem.second.setVolume(100);
        if (elem.second.getStatus() == sf::SoundSource::Paused) {
          elem.second.play();
        }
        break;
    }
  }
  SetObject("settings", "volume", 0,
            "Volume: " + bs::atos(m_music["main"].getVolume()));
}

void GameWindow::Ficha() {
  m_music["main"].stop();
  m_music["game"].stop();
  m_movie.play();
  while (true) {
    m_movie.update();
    clear();
    draw(m_movie);
    display();
  }
}
>>>>>>> dev-ntheme

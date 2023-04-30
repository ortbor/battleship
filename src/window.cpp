#include "../lib/window.hpp"

#include "../lib/button.hpp"
#include "../lib/object.hpp"

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

Music& GameWindow::GetMusic(const string& elem) { return music_[elem]; }

string& GameWindow::GetBox() { return text_box_; }

void GameWindow::SetObject(const string& scene, const string& elem,
                           size_t index, const string& str) {
  dynamic_cast<Text*>(
      buttons_[scene][elem].get()->GetDrawable()[index].sprite.get())
      ->setString(str);
  DrawObjects();
}

void GameWindow::SetButtons(const string& str) {
  button_str_ = str;
  DrawObjects();
}

void GameWindow::SetShow(const string& scene, const string& elem, size_t index,
                         bool show) {
  buttons_[scene][elem].get()->GetDrawable()[index].show = show;
  DrawObjects();
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

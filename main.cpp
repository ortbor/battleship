#include <iostream>

#include "lib/game.hpp"

int main() {
  const size_t kSize = 10;
  const size_t kShips = 2;

  /*sf::RenderWindow wnd;
  wnd.create(VideoMode(1920, VideoMode::getDesktopMode().height), "sds");

  sf::View view;
  view.setSize(1920, VideoMode::getDesktopMode().height);
  view.setCenter(Vector2f(view.getSize().x / 2, view.getSize().y / 2));
  wnd.setView(view);

  Texture background;
  if (!background.loadFromFile(Path().string() + kRes + "background.jpg")) {
    throw std::runtime_error("Cannot load background");
  }
  sf::Sprite str(background);

  Event event;
  while (wnd.isOpen()) {
    while (wnd.pollEvent(event)) {
      if (event.type == Event::MouseButtonPressed) {
        std::cout << (Mouse::getPosition().y - wnd.getPosition().y) * 1080 /
                         wnd.getSize().y
                  << ' ' << Mouse::getPosition().y << ' ' << wnd.getPosition().y
                  << ' '
                  << wnd.mapPixelToCoords(Mouse::getPosition()).y *
                         wnd.getSize().y / 1080
                  << '\n';

        if (event.type == Event::Resized) {
          wnd.setView(view);
        }
      }
    }
    wnd.clear();
    wnd.draw(str);
    wnd.display();
  }*/

  GameLoop game(Vector2f(kSize, kSize), kShips);
  game.Go();

  return 0;
}

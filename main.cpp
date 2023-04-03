#include <iostream>

#include "lib/game.hpp"

int main() {
  const size_t kSize = 10;
  const size_t kShips = 1;

  GameLoop game(Vector2f(kSize, kSize), kShips);
  game.StartMenu();

  return 0;
}

#include <iostream>

#include "lib/game.hpp"

int main() {
  const size_t kSize = 10;
  const size_t kShips = 10;

  GameLoop game(Vector2f(kSize, kSize), kShips);
  game.Play();

  return 0;
}

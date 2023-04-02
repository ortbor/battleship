#include <iostream>

#include "lib/game.hpp"

int main() {
  const size_t kSize = 2;
  const size_t kShips = 2;

  GameLoop game(Vector2f(kSize, kSize), kShips);
  game.Play();

  return 0;
}

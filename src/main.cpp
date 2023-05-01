#include <iostream>

#include "../lib/game.hpp"

int main() {
  const size_t kSize = 10;
  const size_t kShips = 2;

  GameLoop game(Vector2u(kSize, kSize), kShips);
  game.Go();

  return 0;
}

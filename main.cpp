#include <iostream>

#include "lib/game.hpp"

int main() {
  const size_t kSize = 10;
  GameLoop game(Vector2f(kSize, kSize));
  game.Play();

  return 0;
}

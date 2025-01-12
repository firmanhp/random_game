#include "game.h"

int main(int argc, char *argv[]) {
  auto game = snek::Game::make();
  game->main_loop();
  return 0;
}
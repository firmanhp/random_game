#include "game.h"

int main(int argc, char *argv[]) {
  auto game = titres::Game::make();
  game->main_loop();
  return 0;
}
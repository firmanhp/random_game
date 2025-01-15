#pragma once

#include "piece.h"
#include "types.h"

namespace titres {

class Game;
class World;

class PlayerPiece {
public:
  PlayerPiece(Game *game, World *world) : game_(game), world_(world) {}
  void init();
  void on_keypress(KeyPress key);
  void draw(std::vector<std::string> &canvas) const;
  void move_down();

private:
  void force_down();

  Game *game_;
  World *world_;
  Piece piece_;
  Piece next_piece_;
  Pos top_left_pos_;
};

} // namespace titres

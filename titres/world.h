#pragma once

#include <string>
#include <vector>

#include "piece.h"
#include "player_piece.h"
#include "types.h"

namespace titres {

class Game;

class World {
public:
  World(Game *game) : game_(game), player_(game, this) {}
  void init(int rows, int cols);
  void on_tick();
  bool is_valid_move(const Piece &piece, const Pos &top_left_pos,
                     bool allow_top_row_crossing = true);
  void draw(std::vector<std::string> &canvas) const;
  void apply(const Piece &piece, const Pos &top_left_pos);
  const std::vector<std::string> &grid() const { return grid_; }
  int rows() const { return grid_.size(); }
  int cols() const { return grid_[0].size(); }
  void on_keypress(KeyPress key);

private:
  void score_check();

  Game *game_;
  PlayerPiece player_;
  std::vector<std::string> grid_;
};

} // namespace titres
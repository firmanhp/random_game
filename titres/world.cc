#include "world.h"
#include "game.h"

namespace titres {

void World::init(int rows, int cols) {
  grid_.resize(rows);
  for (auto &row : grid_) {
    row.resize(cols, ' ');
  }
  player_.init();
}

void World::on_tick() { player_.move_down(); }

bool World::is_valid_move(const Piece &piece, const Pos &top_left_pos,
                          bool allow_top_row_crossing) {
  for (int r = 0; r < Piece::ROWS; ++r)
    for (int c = 0; c < Piece::COLS; ++c) {
      if (piece.data[r][c] == '0' ||
          (allow_top_row_crossing && top_left_pos.row + r < 0))
        continue;

      // do not let real tile go outside of the grid
      if ((top_left_pos.col + c < 0) || (top_left_pos.col + c >= cols()) ||
          (top_left_pos.row + r < 0) || (top_left_pos.row + r >= rows()))
        return false;

      if (grid_[top_left_pos.row + r][top_left_pos.col + c] == '1')
        return false;
    }

  return true;
}

void World::on_keypress(KeyPress key) { player_.on_keypress(key); }

void World::draw(std::vector<std::string> &canvas) const {
  canvas = grid_; // copy
  player_.draw(canvas);
}

void World::apply(const Piece &piece, const Pos &top_left_pos) {
  if (!is_valid_move(piece, top_left_pos, /*allow_top_row_crossing*/ false)) {
    player_.draw(grid_); // draw losing position
    game_->stop();
    return;
  }
  player_.draw(grid_);
  score_check();
}

void World::score_check() {
  // todo
}

} // namespace titres
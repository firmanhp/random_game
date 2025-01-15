#include "player_piece.h"

#include "game.h"
#include "world.h"

namespace titres {

void PlayerPiece::init() {
  piece_ = PIECES[rand() % PIECES.size()];
  next_piece_ = PIECES[rand() % PIECES.size()];
  top_left_pos_ = Pos{.row = -Piece::ROWS, .col = 0};
}

void PlayerPiece::on_keypress(KeyPress key) {
  Pos next_pos = top_left_pos_;
  Piece next_piece = piece_;
  switch (key) {
  case KeyPress::kUp: {
    next_piece = piece_.rotate_ccw();
    break;
  }
  case KeyPress::kDown: {
    return force_down();
  }
  case KeyPress::kLeft:
  case KeyPress::kRight: {
    next_pos = top_left_pos_ + POS_VEC[static_cast<int>(key)];
    break;
  }
  }

  if (world_->is_valid_move(next_piece, next_pos)) {
    piece_ = next_piece;
    top_left_pos_ = next_pos;
  }
}

void PlayerPiece::force_down() {
  while (world_->is_valid_move(
      piece_, top_left_pos_ + POS_VEC[static_cast<int>(KeyPress::kDown)])) {
    top_left_pos_ = top_left_pos_ + POS_VEC[static_cast<int>(KeyPress::kDown)];
  }
}

void PlayerPiece::move_down() {
  if (auto next_pos =
          top_left_pos_ + POS_VEC[static_cast<int>(KeyPress::kDown)];
      world_->is_valid_move(piece_, next_pos)) {
    top_left_pos_ = next_pos;
    return;
  }

  world_->apply(piece_, top_left_pos_);
  piece_ = next_piece_;
  next_piece_ = PIECES[rand() % PIECES.size()];
  top_left_pos_ = Pos{.row = -Piece::ROWS, .col = 0};
}

void PlayerPiece::draw(std::vector<std::string> &canvas) const {
  for (int r = 0; r < Piece::ROWS; ++r)
    for (int c = 0; c < Piece::COLS; ++c) {
      if (piece_.data[r][c] == '0' || (top_left_pos_.row + r < 0) ||
          (top_left_pos_.col + c < 0) ||
          (top_left_pos_.col + c >= world_->cols()) ||
          ((top_left_pos_.row + r >= world_->rows())))
        continue;

      canvas[top_left_pos_.row + r][top_left_pos_.col + c] = '1';
    }
}

} // namespace titres
#include "snake.h"

#include "config.h"
#include "food.h"
#include "game.h"
#include "world.h"

#include <cassert>
#include <span>
#include <vector>

namespace snek {

void Snake::init() {
  const int mid_row = world_->rows() / 2, mid_col = world_->cols() / 2;
  body_.push_back(Pos{.row = mid_row, .col = mid_col});
  body_.push_back(Pos{.row = mid_row, .col = mid_col - 1});
  body_.push_back(Pos{.row = mid_row, .col = mid_col - 2});
}

void Snake::move(Direction direction) {
  // Do not move in opposite direction
  if ((direction == Direction::kDown && direction_ == Direction::kUp) ||
      (direction == Direction::kUp && direction_ == Direction::kDown) ||
      (direction == Direction::kLeft && direction_ == Direction::kRight) ||
      (direction == Direction::kRight && direction_ == Direction::kLeft)) {
    // do nothing
  } else {
    direction_ = direction;
  }
  popped_tail_ = body_.back();
  for (int i = (int)body_.size() - 1; i > 0; --i) {
    body_[i] = body_[i - 1];
  }

  body_[0] = body_[0] + POS_VEC[static_cast<uint8_t>(direction_)];
  const int rows = world_->rows();
  const int cols = world_->cols();
  body_[0].row += rows;
  body_[0].row %= rows;
  body_[0].col += cols;
  body_[0].col %= cols;
}

void Snake::on_collision(const Food & /*food*/) {
  assert(popped_tail_.has_value());
  body_.push_back(*popped_tail_);
  game_->inc_score(FOOD_SCORE);
}

void Snake::on_collision(const Snake & /*snake*/) { game_->stop(); }

void Snake::place_render(std::vector<std::string> &grid) const {
  for (auto p : body_) {
    grid[p.row][p.col] = 'x';
  }
  const Pos head = body_[0];
  switch (direction_) {
  case Direction::kUp: {
    grid[head.row][head.col] = '^';
    break;
  }
  case Direction::kDown: {
    grid[head.row][head.col] = 'v';
    break;
  }
  case Direction::kLeft: {
    grid[head.row][head.col] = '<';
    break;
  }
  case Direction::kRight: {
    grid[head.row][head.col] = '>';
    break;
  }
  }
}
} // namespace snek
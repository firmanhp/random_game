#include "food.h"

#include "game.h"
#include "snake.h"
#include "world.h"

#include <cassert>
#include <unordered_set>

namespace snek {

void Food::reposition(std::span<const Pos> banned_pos) {
  std::unordered_set<Pos> ban_set;
  for (auto pos : banned_pos) {
    ban_set.insert(pos);
  }

  std::vector<Pos> safe_pos;
  const int rows = world_->rows();
  const int cols = world_->cols();
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      Pos pos{.row = i, .col = j};
      if (ban_set.contains(pos))
        continue;
      safe_pos.push_back(pos);
    }
  }

  if (safe_pos.size() == 0) {
    game_->stop();
  }
  pos_ = safe_pos[rand() % safe_pos.size()];
}

void Food::on_collision(const Snake &snake) {
  reposition(/*banned_pos*/ snake.pos());
}

void Food::place_render(std::vector<std::string> &grid) const {
  grid[pos_.row][pos_.col] = 'o';
}

} // namespace snek
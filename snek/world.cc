#include "world.h"

#include <curses.h>
#include <iostream>

namespace snek {

void World::init(int rows, int cols) {
  grid_.resize(rows);
  for (auto &row : grid_) {
    row.resize(cols);
  }
  snake_.init();
  food_.reposition(/*banned_pos=*/snake_.pos());
}

void World::on_tick(Direction user_direction) {
  snake_.move(user_direction);
  collision_check();
  grid_clear();
  snake_.place_render(grid_);
  food_.place_render(grid_);
}

void World::grid_clear() {
  for (int i = 0; i < rows(); ++i) {
    for (int j = 0; j < cols(); ++j) {
      grid_[i][j] = ' ';
    }
  }
}

void World::collision_check() {
  std::unordered_set<Pos> pos;
  for (auto p : snake_.pos()) {
    if (pos.contains(p)) {
      snake_.on_collision(snake_);
      break;
    }
    pos.insert(p);
  }

  for (auto p : food_.pos()) {
    if (pos.contains(p)) {
      snake_.on_collision(food_);
      food_.on_collision(snake_);
      break;
    }
    pos.insert(p);
  }
}

} // namespace snek
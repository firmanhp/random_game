#pragma once

#include "food.h"
#include "snake.h"
#include "types.h"

#include <vector>

namespace snek {

class Game;

class World {
public:
  World(Game *game) : game_(game), snake_(game, this), food_(game, this) {}

  void init(int rows, int cols);

  int rows() const { return grid_.size(); }
  int cols() const { return grid_[0].size(); }

  void on_tick(Direction user_direction);
  const std::vector<std::string> &grid() const { return grid_; }

private:
  void grid_clear();
  void collision_check();

  Game *game_;
  Snake snake_;
  Food food_;
  std::vector<std::string> grid_;
};

} // namespace snek
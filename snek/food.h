#pragma once

#include "types.h"
#include <span>

namespace snek {

class Snake;
class World;
class Game;

class Food {
public:
  Food(Game *game, World *world) : game_(game), world_(world) {}
  void init() {}

  void reposition(std::span<const Pos> banned_pos);
  std::span<const Pos> pos() const { return std::span<const Pos>{&pos_, 1}; }
  void on_collision(const Snake &snake);
  void place_render(std::vector<std::string> &grid) const;

private:
  Game *game_;
  World *world_;
  Pos pos_;
};

} // namespace snek
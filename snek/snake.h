#pragma once

#include "types.h"

#include <span>

namespace snek {

class World;
class Game;
class Food;

class Snake {
public:
  Snake(Game *game, World *world)
      : game_(game), world_(world), direction_(Direction::kRight) {}

  void init();
  void move(Direction direction);
  std::span<const Pos> pos() const { return body_; }
  Direction direction() const { return direction_; }

  void on_collision(const Food & /*food*/);
  void on_collision(const Snake & /*snake*/);

  void place_render(std::vector<std::string> &grid) const;

private:
  Game *game_;
  World *world_;
  std::vector<Pos> body_; // head at [0]
  // to be used as extension when collision with food
  std::optional<Pos> popped_tail_;
  Direction direction_;
};

} // namespace snek
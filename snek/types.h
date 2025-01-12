#pragma once

#include <chrono>
#include <cstdint>
#include <unordered_set>

namespace snek {

enum class Direction : uint8_t {
  kUp,
  kDown,
  kLeft,
  kRight,
};

struct Pos {
  int row, col;
  Pos operator+(const Pos &other) {
    return Pos{.row = row + other.row, .col = col + other.col};
  }

  bool operator==(const Pos &other) const = default;
};

constexpr Pos POS_VEC[4] = {
    Pos{.row = -1, .col = 0},
    Pos{.row = 1, .col = 0},
    Pos{.row = 0, .col = -1},
    Pos{.row = 0, .col = 1},
};

} // namespace snek

template <> struct std::hash<snek::Pos> {
  size_t operator()(const snek::Pos &pos) const {
    return std::hash<int>{}(pos.row) ^ std::hash<int>{}(pos.col);
  }
};

inline std::ostream &operator<<(std::ostream &o, const snek::Pos &p) {
  o << p.row << ',' << p.col;
  return o;
}
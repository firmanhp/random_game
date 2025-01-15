#pragma once

#include <cstdint>
#include <ostream>
#include <utility>

namespace titres {

enum class KeyPress : uint8_t {
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

} // namespace titres

template <> struct std::hash<titres::Pos> {
  size_t operator()(const titres::Pos &pos) const {
    return std::hash<int>{}(pos.row) ^ std::hash<int>{}(pos.col);
  }
};

inline std::ostream &operator<<(std::ostream &o, const titres::Pos &p) {
  o << p.row << ',' << p.col;
  return o;
}

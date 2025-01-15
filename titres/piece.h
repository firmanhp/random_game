#pragma once

#include <array>

namespace titres {

struct Piece {
  static constexpr int ROWS = 4;
  static constexpr int COLS = 4;
  char data[ROWS][COLS + 1];

  Piece rotate_ccw() const {
    Piece piece;
    for (int i = 0; i < ROWS; ++i) {
      piece.data[i][COLS] = '\0';
    }
    for (int i = 0; i < ROWS; ++i) {
      for (int j = 0; j < COLS; ++j) {
        piece.data[i][j] = data[j][COLS - i - 1];
      }
    }
    return piece;
  }
};

// Square so we can rotate them easily
constexpr std::array<Piece, 7> PIECES = {
    Piece{{
        "1000", // I
        "1000", //
        "1000", //
        "1000", //
    }},
    Piece{{
        "0000", // O
        "0000", //
        "1100", //
        "1100", //
    }},
    Piece{{
        "0000", // S
        "0000", //
        "0110", //
        "1100", //
    }},
    Piece{{
        "0000", // Z
        "0000", //
        "1100", //
        "0110", //
    }},
    Piece{{
        "0000", // L
        "1000", //
        "1000", //
        "1100", //
    }},
    Piece{{
        "0000", // J
        "0100", //
        "0100", //
        "1100", //
    }},
    Piece{{
        "0000", // T
        "0000", //
        "1110", //
        "0100", //
    }},
};

} // namespace titres
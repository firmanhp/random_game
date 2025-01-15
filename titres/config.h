#pragma once

#include <chrono>

namespace titres {

using namespace std::chrono_literals;
constexpr std::chrono::duration TICK = 750ms;

constexpr int WORLD_ROWS = 15;
constexpr int WORLD_COLS = 15;
constexpr int ROW_SCORE = 10;
constexpr int MAX_LOG = 10;

} // namespace titres
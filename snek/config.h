#pragma once

#include <chrono>

namespace snek {

using namespace std::chrono_literals;
constexpr std::chrono::duration TICK = 100ms;
constexpr int WORLD_ROWS = 50;
constexpr int WORLD_COLS = 50;
constexpr int FOOD_SCORE = 10;
constexpr int MAX_LOG = 10;

} // namespace snek
#pragma once

#include "world.h"
#include <list>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <thread>

namespace snek {

class Input {
public:
  Input() {}
  ~Input() { stop(); }
  void init();
  void stop() { stopped_ = true; }
  Direction direction() { return direction_; }

private:
  void listen();

  std::thread thread_;
  volatile Direction direction_;
  volatile bool stopped_;
};

class Game;

class Logger {
public:
  Logger(Game *game) : game_(game), ss_() {}
  ~Logger();
  template <typename T> Logger &operator<<(const T &other) {
    ss_ << other;
    return *this;
  }

private:
  Game *game_;
  std::istringstream ss_;
};

class Game {
public:
  ~Game();
  static std::unique_ptr<Game> make();
  Game() : score_(0), input_(std::make_unique<Input>()), world_(this) {}
  void main_loop();
  void inc_score(int inc) { score_ += inc; }
  void stop() { game_over_ = true; }
  Logger log() { return Logger(this); }
  void on_log(std::string logstr);

private:
  void init();
  void tick();
  void game_over_tick();
  void render();
  void render_game_over();
  void render_log();

  int score_;
  std::unique_ptr<Input> input_;
  World world_;
  bool game_over_ = false;
  WINDOW *game_window_;
  WINDOW *debug_;
  std::list<std::string> logs_;
};

} // namespace snek
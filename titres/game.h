#pragma once

#include "types.h"
#include "world.h"
#include <list>
#include <ncurses.h>
#include <sstream>
#include <string>
#include <thread>

namespace titres {

class Game;

class Input {
public:
  Input(Game *game) : game_(game) {}
  ~Input() { stop(); }
  void init();
  void stop() { stopped_ = true; }

private:
  void listen();

  Game *game_;
  std::thread thread_;
  volatile bool stopped_;
};

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
  Game() : score_(0), input_(this), world_(this) {}
  void main_loop();
  void inc_score(int inc) { score_ += inc; }
  void stop() { game_over_ = true; }
  Logger log() { return Logger(this); }
  void on_log(std::string logstr);
  void on_keypress(KeyPress key);

private:
  void init();
  void tick();
  void game_over_tick();
  void render();
  void render_log();

  int score_;
  Input input_;
  World world_;
  bool game_over_ = false;
  WINDOW *game_window_;
  WINDOW *debug_;
  std::list<std::string> logs_;
};

} // namespace titres
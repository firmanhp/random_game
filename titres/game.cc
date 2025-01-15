#include "game.h"
#include "config.h"

#include <iostream>
#include <ncurses.h>

namespace titres {

void Input::listen() {
  while (!stopped_) {
    switch (getch()) {
    case KEY_UP: {
      game_->on_keypress(KeyPress::kUp);
      break;
    }
    case KEY_DOWN: {
      game_->on_keypress(KeyPress::kDown);
      break;
    }
    case KEY_LEFT: {
      game_->on_keypress(KeyPress::kLeft);
      break;
    }
    case KEY_RIGHT: {
      game_->on_keypress(KeyPress::kRight);
      break;
    }
    }
  }
}

void Input::init() {
  keypad(stdscr, TRUE); // Enable special keys
  thread_ = std::thread([this]() { listen(); });
}

std::unique_ptr<Game> Game::make() {
  std::unique_ptr<Game> game = std::make_unique<Game>();
  game->init();
  game->world_.init(WORLD_ROWS, WORLD_COLS);
  game->input_.init();
  return game;
}

Game::~Game() {}

void Game::main_loop() {
  while (true) {
    std::this_thread::sleep_for(TICK);
    tick();
  }
}

void Game::init() {
  srand(time(NULL));
  initscr();
  cbreak();
  noecho();
  curs_set(0);

  int scr_h, scr_w;
  getmaxyx(stdscr, scr_h, scr_w);
  const int win_h = WORLD_ROWS + 4; // padding
  const int win_w = WORLD_COLS + 2; // padding

  // center
  const int start_row = (scr_h - win_h) / 2;
  const int start_col = (scr_w - win_w) / 2;
  game_window_ = newwin(win_h, win_w, start_row, start_col);
  box(game_window_, 0, 0);
}

void Game::tick() {
  if (game_over_) {
    return game_over_tick();
  }

  world_.on_tick();
  render();
}

void Game::game_over_tick() {}

void Game::render() {
  std::vector<std::string> canvas;
  world_.draw(canvas);

  if (game_over_) {
    mvwprintw(game_window_, 1, 1, "Game over.", score_);
  }
  mvwprintw(game_window_, 2, 1, "Score: %d", score_);
  for (int i = 0; i < (int)canvas.size(); ++i) {
    // +1, +2 for accomodate padding
    mvwprintw(game_window_, i + 3, 1, "%s", canvas[i].c_str());
  }
  wrefresh(game_window_);
}

void Game::on_keypress(KeyPress key) {
  world_.on_keypress(key);
  render();
}

void Game::on_log(std::string logstr) {
  logs_.push_back(std::move(logstr));
  while (logs_.size() > MAX_LOG) {
    logs_.pop_front();
  }
}

Logger::~Logger() { game_->on_log(std::move(ss_).str()); }

} // namespace titres
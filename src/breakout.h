#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "game_state.h"

#define TARGET_ROWS 10
#define TARGET_COLS 4

typedef struct Target {
  bool killed;
  SDL_Color color;
  SDL_Rect rect;
} Target;

typedef struct Breakout {
  SDL_Rect ball;
  int ball_speed;
  int ball_xdir;
  int ball_ydir;
  SDL_Rect player;
  int player_xdir;
  Target targets[TARGET_COLS][TARGET_ROWS];
  bool ball_attached;
  bool game_running;
} Breakout;

Breakout create_breakout(SDL_Renderer *renderer, int screen_width,
                         int screen_height);

void update_breakout(int screen_width, int screen_height, Breakout *breakout);
void events_breakout(SDL_Event e, SDL_Renderer *renderer, int screen_width,
                     int screen_height, Breakout *breakout);
void render_breakout(SDL_Renderer *renderer, Breakout breakout);

#endif

#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "game_state.h"

#define TARGET_COLS 8
#define TARGET_ROWS 15
#define MAX_TARGETS TARGET_ROWS * TARGET_COLS

typedef struct Target {
  bool killed;
  SDL_Color color;
  SDL_Rect rect;
} Target;

typedef struct Breakout {
  SDL_Rect ball;
  int ball_speed;
  int xdir;
  int ydir;
  SDL_Rect player;
  Target targets[MAX_TARGETS];
  bool game_running;
} Breakout;

Breakout create_breakout(SDL_Renderer *renderer, int screen_width,
                         int screen_height);

void update_breakout(int screen_width, int screen_height, Breakout *breakout);
void events_breakout(SDL_Event e, SDL_Renderer *renderer, int screen_width,
                     int screen_height, Breakout *breakout);
void render_breakout(SDL_Renderer *renderer, Breakout breakout);

#endif

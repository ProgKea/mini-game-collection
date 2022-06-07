#ifndef BREAKOUT_H
#define BREAKOUT_H

#include <SDL2/SDL.h>
#include <stdbool.h>

#include "game_state.h"

#define MAX_TARGETS 10

typedef struct Breakout {
  SDL_Rect ball;
  int ball_speed;
  int xdir;
  int ydir;
  SDL_Rect player;
  SDL_Rect targets[];
} Breakout;

Breakout create_breakout(SDL_Renderer *renderer, int screen_width,
                         int screen_height);

void update_breakout(int screen_width, int screen_height, Breakout *breakout);
void events_breakout(SDL_Event e, SDL_Renderer *renderer, int screen_width,
                     int screen_height, Breakout *breakout);
void render_breakout(SDL_Renderer *renderer, Breakout breakout);

#endif

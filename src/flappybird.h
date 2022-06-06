#ifndef FLAPPYBIRD_H
#define FLAPPYBIRD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>

#include "game_state.h"

#define MAX_TUBES 4

typedef struct FlappyBird {
  SDL_Rect rect;
  Mix_Chunk *flap_sound;
  bool is_bird;
  bool can_jump;
  float vel_y;
  SDL_Rect bot_tubes[MAX_TUBES];
  SDL_Rect top_tubes[MAX_TUBES];
  int scroll_speed;
  int last_tube;
  bool game_running;
} FlappyBird;

FlappyBird create_bird(SDL_Renderer *renderer, int screen_width,
                       int screen_height);

void render_flappybird(SDL_Renderer *renderer, FlappyBird bird);
void events_flappybird(SDL_Event e, SDL_Renderer *renderer, int screen_width,
                       int screen_height, FlappyBird *bird);
void update_flappybird(int screen_width, int screen_height, FlappyBird *bird);
void destroy_flappybird(FlappyBird bird);

#endif

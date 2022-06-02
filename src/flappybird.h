#ifndef FLAPPYBIRD_H
#define FLAPPYBIRD_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

typedef struct FlappyBird {
  SDL_Rect rect;
  Mix_Chunk *flap_sound;
  bool is_bird;
  float vel_y;
  bool can_jump;
} FlappyBird;

FlappyBird create_bird(SDL_Renderer *renderer, int screen_width);

void render_flappybird(SDL_Renderer *renderer, FlappyBird bird);
void events_flappybird(SDL_Event e, FlappyBird *bird);
void update_bird(FlappyBird *bird);

#endif

#include "init.h"

SDL_Window *win = NULL;
SDL_Renderer *renderer = NULL;

void init_sdl2() {
  if (TTF_Init() > 0) {
    fprintf(stderr, "Failed to init SDL_ttf: %s\n", SDL_GetError());
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) > 0)
    fprintf(stderr, "Failed to init SDL: %s\n", SDL_GetError());

  // if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
  // fprintf(stderr, "Failed to init SDL_image: %s\n", SDL_GetError());

  win =
      SDL_CreateWindow("bad game", SDL_WINDOWPOS_CENTERED,
                       SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
  if (win == NULL)
    fprintf(stderr, "Failed to create window: %s\n", SDL_GetError());

  renderer = SDL_CreateRenderer(
      win, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
  if (renderer == NULL)
    fprintf(stderr, "Failed to create renderer: %s\n", SDL_GetError());

  init_menu_items(renderer, WIDTH);
}
